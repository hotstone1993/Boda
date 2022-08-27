#ifndef BODA_FBXPARSER_H
#define BODA_FBXPARSER_H

#include "BaseParser.h"

#include <fbxsdk.h>

class FBXParser: public BaseParser {
public:
    FBXParser();
    virtual ~FBXParser();
    bool createBSSFile(const char* filePath) override;
    bool getVertex(FbxNode* node, Mesh& m);
private:
    void destory();

    FbxManager* manager = nullptr;
    FbxScene* scene = nullptr;
};

#endif // BODA_FBXPARSER_H