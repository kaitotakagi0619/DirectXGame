#include "Player.h"
#include "Input.h"
#include "DebugText.h"
#include "SphereCollider.h"
#include "ParticleManager.h"

using namespace DirectX;

Player* Player::Create(Model* model)
{
	// 3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	Player* instance = new Player();
	if (instance == nullptr)
	{
		return nullptr;
	}

	// ������
	if (!instance->Initialize())
	{
		delete instance;
		assert(0);
	}

	if (model)
	{
		instance->SetModel(model);
	}

	return instance;
}

bool Player::Initialize()
{
	if (!Object3d::Initialize())
	{
		return false;
	}

	// �R���C�_�[�̒ǉ�
	float radius = 0.6f;
	//���a�������������畂�������W�����̒��S�ɂ���
	SetCollider(new SphereCollider(XMVECTOR({ 0,radius,0,0 }), 1.3f));

	return true;
}

void Player::Update()
{
	Input* input = Input::GetInstance();

	if (input->PushKey(DIK_A))
	{
		rotation.y -= 2.0f;
	}
	else if (input->PushKey(DIK_D))
	{
		rotation.y += 2.0f;
	}

	XMVECTOR move = { 0,0,0.1f,0 };
	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(rotation.y));
	move = XMVector3TransformNormal(move, matRot);

	if (input->PushKey(DIK_S))
	{
		position.x -= move.m128_f32[0];
		position.y -= move.m128_f32[1];
		position.z -= move.m128_f32[2];
	}
	else if (input->PushKey(DIK_S))
	{
		position.x += move.m128_f32[0];
		position.y += move.m128_f32[1];
		position.z += move.m128_f32[2];
	}

	Object3d::Update();
}

void Player::OnCollision(const CollisionInfo& info)
{
	//�f�o�b�N�e�L�X�g
	DebugText::GetInstance()->Printf("Collision detected");

	//�Փ˓_�Ƀp�[�e�B�N���𔭐�����
	for (int i = 0; i < 1; ++i)
	{

		const float rnd_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

		ParticleManager::GetInstance()->Add(10, XMFLOAT3(info.inter.m128_f32), vel, XMFLOAT3(), 0.0f, 1.0f);
	}
}