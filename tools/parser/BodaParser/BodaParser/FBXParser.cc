#include "FBXParser.h"
#include "directxmath.h"
using namespace DirectX;


FBXParser::FBXParser() {
}

FBXParser::~FBXParser() {
    destory();
}

void FBXParser::destory() {
    if (manager != nullptr)
        manager->Destroy();
    if (scene != nullptr)
        scene->Destroy();
}

bool initializeFbxObjects(FbxManager*& manager, FbxScene*& scene) {
    if (!manager) {
        std::cout << "Error: Unable to create FBX Manager!\n";
        return false;
    }
    else {
        std::cout << "Autodesk FBX SDK version: " << manager->GetVersion() << "\n";
    }

    FbxIOSettings* ios = FbxIOSettings::Create(manager, IOSROOT);
    manager->SetIOSettings(ios);

    FbxString lPath = FbxGetApplicationDirectory();
    manager->LoadPluginsDirectory(lPath.Buffer());

    scene = FbxScene::Create(manager, "My Scene");
    if (!scene)
    {
        std::cout << "Error: Unable to create FBX scene!\n";
        return false;
    }

    return true;
}

bool loadScene(FbxManager* manager, FbxDocument* scene, const char* filePath) {
    FbxImporter* importer = FbxImporter::Create(manager, "");

    if (!importer->Initialize(filePath, -1, manager->GetIOSettings())) {
        std::cout << "Call to FbxImporter::Initialize() failed.\n";
        importer->Destroy();
        return false;
    }

    if (!importer->IsFBX()) {
        importer->Destroy();
        return false;
    }

    if (!importer->Import(scene)) {
        importer->Destroy();
        return false;
    }

    return true;
}

void getLocalMatrix(FbxNode* node, float (&mat)[16]) {
    FbxAMatrix matrixGeo;
    matrixGeo.SetIdentity();
    if (node->GetNodeAttribute())
    {
        const FbxVector4 lT = node->GetGeometricTranslation(FbxNode::eSourcePivot);
        const FbxVector4 lR = node->GetGeometricRotation(FbxNode::eSourcePivot);
        const FbxVector4 lS = node->GetGeometricScaling(FbxNode::eSourcePivot);
        matrixGeo.SetT(lT);
        matrixGeo.SetR(lR);
        matrixGeo.SetS(lS);
    }
    FbxAMatrix globalMatrix = node->EvaluateLocalTransform();

    FbxAMatrix matrix = globalMatrix * matrixGeo;
    for (int c = 0; c < 4; ++c) {
        FbxVector4 vector = matrix.GetRow(c);
        for (int r = 0; r < 4; ++r) {
            mat[4 * c + r] = vector.mData[r];
        }
    }
}

bool FBXParser::getVertex(FbxNode* node, Mesh& m)
{
    if (node == nullptr)
        return false;

    // std::cout << "노드 이름: " << node->GetName() << std::endl;

    getLocalMatrix(node, m.mat);
    FbxMesh* mesh = node->GetMesh();

    if (mesh != nullptr) {
        const unsigned int count = mesh->GetControlPointsCount();
        for (unsigned int idx = 0; idx < count; ++idx) {
            m.positions.emplace_back(mesh->GetControlPointAt(idx).mData[0], mesh->GetControlPointAt(idx).mData[1], mesh->GetControlPointAt(idx).mData[2]);
        }
        FbxGeometryElementNormal* normalElement = mesh->GetElementNormal();
        if (normalElement != nullptr) {
            if (normalElement->GetMappingMode() == FbxGeometryElement::eByControlPoint) {
                for (int idx = 0; idx < count; idx++)
                {
                    int normalIndex = 0;
                    if (normalElement->GetReferenceMode() == FbxGeometryElement::eDirect)
                        normalIndex = idx;
                    else if (normalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
                        normalIndex = normalElement->GetIndexArray().GetAt(idx);

                    FbxVector4 normal = normalElement->GetDirectArray().GetAt(normalIndex);
                    m.normals.emplace_back(normal[0], normal[1], normal[2]);
                }
            }
            else if (normalElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex) {
                for (unsigned int i = 0; i < count; ++i) {
                    FbxVector4 normal = normalElement->GetDirectArray().GetAt(i);
                    m.normals.emplace_back(normal[0], normal[1], normal[2]);
                }
            }
        }

        unsigned int triMeshCount = mesh->GetPolygonCount();
        INDEX idx;
        for (unsigned int i = 0; i < triMeshCount; ++i) // 삼각형의 개수
        {
            for (unsigned int j = 0; j < 3; ++j) // 삼각형은 세 개의 정점으로 구성
            {
                idx.data[j] = mesh->GetPolygonVertex(i, j);
            }
            m.indices.push_back(idx);
        }
    }

    int nodeCount = node->GetChildCount();
    for (unsigned int idx = 0; idx < nodeCount; idx++)
    {
        m.children.emplace_back();
        if (!getVertex(node->GetChild(idx), m.children.back()))
            return false;
    }
    return true;
}

bool FBXParser::createBSSFile(const char* filePath) {
    manager = FbxManager::Create();
    
    if (!initializeFbxObjects(manager, scene)) {
        destory();
        return false;
    }

    if (!loadScene(manager, scene, filePath)) {
        destory();
        return false;
    }

    FbxGeometryConverter geometryConverter(manager);
    if (!geometryConverter.Triangulate(scene, true)) {
        destory();
        return false;
    }

    FbxNode* rootNode = scene->GetRootNode();

    if (!getVertex(rootNode, root)) {
        destory();
        return false;
    }

    if (!writeBssFile(filePath)) {
        destory();
        return false;
    }

    destory();

    return true;
}