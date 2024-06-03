#include "MapChipFeild.h"
#include <fstream>
#include <sstream>

void MapChipFeild::ResetMapChipData() {
	// マップチップデータをリセット
	mapChipData_.data.clear();
	mapChipData_.data.resize(knumBlockVirtical);
	for (std::vector<MapChipType>& mapChipDataLine : mapChipData_.data) {
		mapChipDataLine.resize(knumBlockHorizontal);
	}
}

void MapChipFeild::LoadMapChipCsv(const std::string& filePath) {
	// マップチップデータをリセット
	ResetMapChipData();

	// ファイルを開く
	std::ifstream file;
	file.open(filePath);
	assert(file.is_open());

	// マップチップCSV
	std::stringstream mapChipCsv;

	// ファイルの内容を文字列ストリームにコピー
	mapChipCsv << file.rdbuf();

	// ファイルを閉じる
	file.close();

	// CSVからマップチップデータを読み込む
	for (uint32_t i = 0; i < knumBlockVirtical; ++i) {
		std::string line;
		getline(mapChipCsv, line);

		// 1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		for (uint32_t j = 0; j < knumBlockHorizontal; ++j) {
			std::string word;
			getline(line_stream, word, ',');

			if (mapChipTable.contains(word)) {
				mapChipData_.data[i][j] = mapChipTable[word];
			}
		}
	}
}

MapChipType MapChipFeild::GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex) { 
	if (xIndex < 0 || knumBlockHorizontal - 1 < xIndex) {
		return MapChipType::kBlank;
	}
	if (yIndex < 0 || knumBlockVirtical - 1 < yIndex) {
		return MapChipType::kBlank;
	}

	return mapChipData_.data[yIndex][xIndex]; 
}

Vector3 MapChipFeild::GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex) { 
	return Vector3(kBlockWidth * xIndex, kBlockHeight * (knumBlockVirtical - 1 - yIndex), 0); 
}

uint32_t MapChipFeild::GetNumBlockVirtical() { return knumBlockVirtical; }

uint32_t MapChipFeild::GetNumBlockHorizontal() { return knumBlockHorizontal; }
