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

DECLARE_SCRIPT(ScriptMenu, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)
protected:
    std::vector<Button*> mAllButtons;
    INTERFACE_SHOW mInterfaceShow;
    bool mShowMenu;
public:

    virtual void Initia() { mAllButtons = std::vector<Button*>(); mInterfaceShow = NOTHING; mShowMenu = false; }
    virtual void Start() {}
    virtual void Update()
    {
        if (gce::GetKey(gce::Keyboard::ENTER) || gce::GetKey(gce::Keyboard::ESCAPE))
        {
            ShowMenu(PAUSE_MENU);

        }

        if (mShowMenu)
        {
            gce::GameManager::s_pInstance->m_deltaTime = 0.f;
        }
    }
    virtual void Destroy()
    {
        int lenght = (int)mAllButtons.size();
        for (int i = lenght; i > -1; i--)
        {
            delete mAllButtons[i];
        }
    }

    virtual void CollisionEnter() {}
    virtual void CollisionStay() {}
    virtual void CollisionExit() {}

    std::vector<Button*> ShowMenu() { mShowMenu = true; return ActiveButton(mInterfaceShow); }
    std::vector<Button*> ShowMenu(INTERFACE_SHOW interfaceShow) { mShowMenu = true; mInterfaceShow = interfaceShow; return ActiveButton(interfaceShow); }
    void HideMenu() { mShowMenu = true; DeactiveAllButton(); }

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

    bool GetShowMenu() { return mShowMenu; }

    std::vector<Button*> SetInterfaceShow(INTERFACE_SHOW interfaceShow) { mInterfaceShow = interfaceShow; if (mShowMenu) { return ActiveButton(interfaceShow); } return std::vector<Button*>(); }
    bool IsInterfaceShow(INTERFACE_SHOW interfaceShow) { return mInterfaceShow == interfaceShow; }
    INTERFACE_SHOW GetInterfaceShow() { return mInterfaceShow; }

    void AddButton(Button* button) { mAllButtons.push_back(button); }
    void AddButton(gce::GameObject* buttonObject, INTERFACE_SHOW show) { mAllButtons.push_back(new Button(buttonObject, show)); }
    std::vector<Button*>* GetAllButtons() { return &mAllButtons; }

    END_SCRIPT

