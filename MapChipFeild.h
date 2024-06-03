#pragma once
#include <cstdint>
#include <cassert>
#include <vector>
#include <map>
#include <string>
#include "Vector3.h"

enum class MapChipType {
	kBlank, // 空白
	kBlock, // ブロック
};

struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
};

namespace {

	std::map<std::string, MapChipType> mapChipTable = {
	    {"0", MapChipType::kBlank},
	    {"1", MapChipType::kBlock},
	};
}

/// <summary>
/// マップチップフィールド
/// </summary>
class MapChipFeild {
private:
	// 1ブロックのサイズ
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;
	// ブロックの個数
	static inline const uint32_t knumBlockVirtical = 20;
	static inline const uint32_t knumBlockHorizontal = 100;

public:
	MapChipData mapChipData_;
	void ResetMapChipData();
	void LoadMapChipCsv(const std::string& filePath);
	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);
	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);
	uint32_t GetNumBlockVirtical();
	uint32_t GetNumBlockHorizontal();
};
