#pragma once

#include "CollisionInfo.h"
#include "Object3d.h"

//�Փ˔���p�֘A�̌^��`
enum CollisionShapeType
{
	SHAPE_UNKNOWN = -1, // ���ݒ�

	COLLISIONSHAPE_SPHERE, // ��
	COLLISIONSHAPE_MESH, // ���b�V��
};

class BaseCollider
{
public:
	BaseCollider() = default;
	virtual ~BaseCollider() = default;

	inline void SetObject(Object3d * object)
	{
		this->object3d = object;
	}

	inline Object3d* GetObject3d()
	{
		return object3d;
	}

	//�X�V
	virtual void Update() = 0;
	//�`��^�C�v�擾
	inline CollisionShapeType GetShapeType() { return shapeType; }

	//�Փˎ��R�[���o�b�N�֐�
	inline void OnCollision(const CollisionInfo& info)
	{
		object3d->OnCollision(info);
	}

	// �����蔻�葮�����Z�b�g
	inline void SetAttribute(unsigned short attribute)
	{
		this->attribute = attribute;
	}

	// �����蔻�葮����ǉ�
	inline void AddAttribute(unsigned short attribute)
	{
		this->attribute |= attribute;
	}

	// �����蔻�葮�����폜
	inline void RemoveAttribute(unsigned short attribute)
	{
		this->attribute &= !attribute;
	}

protected:
	Object3d* object3d = nullptr;
	//�`��^�C�v
	CollisionShapeType shapeType = SHAPE_UNKNOWN;
	// �����蔻�葮��
	unsigned short attribute = 0b1111111111111111;
};