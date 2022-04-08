#pragma once

#include "Sprite.h"
#include <Windows.h>
#include <string>

// デバッグ用文字表示
class DebugText
{

public:// 静的メンバ関数
	static DebugText* GetInstance();

public:	
	// デバッグテキスト用のテクスチャ番号を指定

	static const int maxCharCount = 256;	// 最大文字数
	static const int fontWidth = 9;			// フォント画像内1文字分の横幅
	static const int fontHeight = 18;		// フォント画像内1文字分の縦幅
	static const int fontLineCount = 14;	// フォント画像内1行分の文字数
	static const int bufferSize = 256;	// 書式付き文字列展開用バッファサイズ

	//コンストラクタ
	DebugText();

	//デストラクタ
	~DebugText();

	//初期化
	void Initialize(UINT texnumber);

	inline void SetPos(float x, float y) {
		posX = x;
		posY = y;
	}

	//代入
	void Print(const std::string & text, float x, float y, float size);
	void NPrint(int len, const char* text);
	void Printf(const char* fmt, ...);

	//描画
	void DrawAll(ID3D12GraphicsCommandList * cmdList);

private:
	// スプライトデータの配列
	Sprite* spriteDatas[maxCharCount] = {};
	// スプライトデータ配列の添え字番号
	int spriteIndex = 0;

	float posX = 0.0f;
	float posY = 0.0f;
	float size = 1.0f;

	char buffer[bufferSize];
};
