#pragma once
#include <GameObject.h>
#include <InputsMethods.h>

enum INTERFACE_SHOW
{
    NOTHING,
    MAIN_MENU,
    PAUSE_MENU,
    SETTING_MENU,
    LOAD_MENU,

    COUNT
};

struct Button
{
    gce::GameObject* mButtonObjet;
    INTERFACE_SHOW mShow;

    Button() { mButtonObjet = nullptr; mShow = NOTHING; }
    Button(gce::GameObject* buttonObjet, INTERFACE_SHOW show) { mButtonObjet = buttonObjet; mShow = show; }

    void SetAll(gce::GameObject* buttonObjet, INTERFACE_SHOW show) { mButtonObjet = buttonObjet; mShow = show; }

    void SetButtonObjet(gce::GameObject* buttonObjet) { mButtonObjet = buttonObjet; }
    gce::GameObject* GetButtonObjet() { return mButtonObjet; }

    void SetInterfaceShow(INTERFACE_SHOW show) { mShow = show; }
    INTERFACE_SHOW GetInterfaceShow() { return mShow; }
};

struct Image
{
    gce::GameObject* mImageObjet;
    INTERFACE_SHOW mShow;

    Image() { mImageObjet = nullptr; mShow = NOTHING; }
    Image(gce::GameObject* buttonObjet, INTERFACE_SHOW show) { mImageObjet = buttonObjet; mShow = show; }

    void SetAll(gce::GameObject* buttonObjet, INTERFACE_SHOW show) { mImageObjet = buttonObjet; mShow = show; }

    void SetImageObjet(gce::GameObject* buttonObjet) { mImageObjet = buttonObjet; }
    gce::GameObject* GetImageObjet() { return mImageObjet; }

    void SetInterfaceShow(INTERFACE_SHOW show) { mShow = show; }
    INTERFACE_SHOW GetInterfaceShow() { return mShow; }
};

DECLARE_SCRIPT(ScriptMenu, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)
protected:
    gce::GameObject* mObjectCamera;
    gce::Vector3f32 mCameraPositionInMenu;
    std::vector<Button*> mAllButtons;
    std::vector<Image*> mAllImages;
    INTERFACE_SHOW mInterfaceShow;
    bool mShowMenu;
public:

    virtual void Initia() { mAllButtons = std::vector<Button*>(); mAllImages = std::vector<Image*>(); mInterfaceShow = NOTHING; mShowMenu = false; }
    virtual void Start() {}
    virtual void Update()
    {
        if (gce::GetKey(gce::Keyboard::ENTER) || gce::GetKey(gce::Keyboard::ESCAPE))
        {
            ShowMenu(PAUSE_MENU);
        }

        if (mShowMenu)
        {
            if (mObjectCamera != nullptr)
            {
                mObjectCamera->transform.SetWorldPosition(mCameraPositionInMenu);
                mObjectCamera->transform.SetLocalRotation(gce::Vector3f32(0.f, 0.f, 0.f));
            }
            gce::GameManager::s_pInstance->m_deltaTime = 0.f;
        }
    }
    virtual void Destroy()
    {
        int lenghtB = (int)mAllButtons.size();
        for (int i = lenghtB; i > -1; i--)
        {
            delete mAllButtons[i];
        }

        int lenghtI = (int)mAllImages.size();
        for (int i = lenghtI; i > -1; i--)
        {
            delete mAllImages[i];
        }
    }

    virtual void CollisionEnter() {}
    virtual void CollisionStay() {}
    virtual void CollisionExit() {}

    std::vector<Button*> ShowMenu() { mShowMenu = true; ActiveImage(mInterfaceShow); return ActiveButton(mInterfaceShow); }
    std::vector<Button*> ShowMenu(INTERFACE_SHOW interfaceShow) { mShowMenu = true; mInterfaceShow = interfaceShow; ActiveImage(interfaceShow); return ActiveButton(interfaceShow); }
    void HideMenu() { mShowMenu = true; DeactiveAllImage(); DeactiveAllButton(); }

    std::vector<Button*> ActiveButton(INTERFACE_SHOW interfaceShow)
    {
        std::vector<Button*> allActiveButton;
        int lenght = (int)mAllButtons.size();
        for (int i = 0; i < lenght; i++)
        {
            Button* button = mAllButtons[i];
            if (button->GetInterfaceShow() == interfaceShow)
            {
                button->GetButtonObjet()->SetActive(true);
                allActiveButton.push_back(button);
            }
            else
            {
                button->GetButtonObjet()->SetActive(false);
            }
        }
        return allActiveButton;
    }

    void DeactiveAllButton()
    {
        int lenght = (int)mAllButtons.size();
        for (int i = 0; i < lenght; i++)
        {
            mAllButtons[i]->GetButtonObjet()->SetActive(false);
        }
    }

    std::vector<Image*> ActiveImage(INTERFACE_SHOW interfaceShow)
    {
        std::vector<Image*> allActiveImage;
        int lenght = (int)mAllImages.size();
        for (int i = 0; i < lenght; i++)
        {
            Image* image = mAllImages[i];
            if (image->GetInterfaceShow() == interfaceShow)
            {
                image->GetImageObjet()->SetActive(true);
                allActiveImage.push_back(image);
            }
            else
            {
                image->GetImageObjet()->SetActive(false);
            }
        }
        return allActiveImage;
    }

    void DeactiveAllImage()
    {
        int lenght = (int)mAllImages.size();
        for (int i = 0; i < lenght; i++)
        {
            mAllImages[i]->GetImageObjet()->SetActive(false);
        }
    }

    bool GetShowMenu() { return mShowMenu; }

    void SetCamera(gce::GameObject* cameraObject) { mObjectCamera = cameraObject; }
    void SetWorldPositionCamera(gce::Vector3f32 pos) { mCameraPositionInMenu = pos; }
    gce::Vector3f32 GetWorldPositionCamera() { return mCameraPositionInMenu; }

    std::vector<Button*> SetInterfaceShow(INTERFACE_SHOW interfaceShow) { mInterfaceShow = interfaceShow; if (mShowMenu) { return ActiveButton(interfaceShow); } return std::vector<Button*>(); }
    bool IsInterfaceShow(INTERFACE_SHOW interfaceShow) { return mInterfaceShow == interfaceShow; }
    INTERFACE_SHOW GetInterfaceShow() { return mInterfaceShow; }

    void AddButton(Button* button) { mAllButtons.push_back(button); }
    void AddButton(gce::GameObject* buttonObject, INTERFACE_SHOW show) { mAllButtons.push_back(new Button(buttonObject, show)); }
    std::vector<Button*>* GetAllButtons() { return &mAllButtons; }

    void AddImage(Image* image) { mAllImages.push_back(image); }
    void AddImage(gce::GameObject* imageObject, INTERFACE_SHOW show) { mAllImages.push_back(new Image(imageObject, show)); }
    std::vector<Image*>* GetAllImages() { return &mAllImages; }

END_SCRIPT

