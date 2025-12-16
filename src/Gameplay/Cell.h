#pragma once
#include <define.h>
#include <Maths/Vector2.hpp>

#define MAX_HEIGHT 10
#define MIN_HEIGHT 0
#define TALL_HEIGHT 50

class GameObject;

class Cell
{
protected:
    int mConfigHeight; // 1 = Classique floor

    gce::Vector2i32 mRowCol;

    bool mIsInaccessible;
    bool mIsAlwaysInaccessible;

    GameObject* mHaveObject;
public:
    Cell() { Start(); }

    void Start() { SetConfigHeight(1);  SetRowCol(-1, -1); SetIsInaccessible(false, false); SetHaveObject(nullptr); }
    
    void OnUpdate() {}

    void ChangeHeight(int newHeight)
    {
        if (newHeight < MIN_HEIGHT) { newHeight = MAX_HEIGHT; }
        else if (newHeight > MAX_HEIGHT) { newHeight = MIN_HEIGHT; }
        mConfigHeight = newHeight;
    }

    void SetAll(int configHeight, gce::Vector2i32 rowCol, bool isInaccessible, GameObject* haveObject) { SetConfigHeight(configHeight);  SetRowCol(rowCol); SetIsInaccessible(isInaccessible); SetHaveObject(haveObject); }

    void SetConfigHeight(int height) { mConfigHeight = height; }
    int GetConfigHeight() { return mConfigHeight; }

    int GetRealHeight() { return TALL_HEIGHT * mConfigHeight; }

    gce::Vector2i32 GetRowCol() { return mRowCol; }
    void SetRowCol(int row, int col) { mRowCol.x = row; mRowCol.y = col; }
    void SetRowCol(gce::Vector2i32 rowcol) { mRowCol = rowcol; }

    void SetIsInaccessible(bool isInaccessible, bool isAlwaysInaccessible) { mIsInaccessible = isInaccessible; mIsAlwaysInaccessible = isAlwaysInaccessible;}
    bool GetIsInaccessible() { return mIsInaccessible; }
    bool GetIsInaccessible() { return mIsAlwaysInaccessible; }

    void SetHaveObject(GameObject* haveObject) { mHaveObject = haveObject; }
    GameObject* GetHaveObject() { return mHaveObject; }

    ~Cell() = default;
};


