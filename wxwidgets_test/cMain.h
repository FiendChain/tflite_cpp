#pragma once

#include <wx/wx.h>
#include "ScreenshotTimer.h"
#include "Model.h"

class cMain: public wxFrame
{
private:
    std::unique_ptr<ScreenshotTimer> m_screenshot_timer;
    std::shared_ptr<Model> m_model;
public:
    cMain();
    ~cMain();
    void onClose(wxCloseEvent& evt);
    wxDECLARE_EVENT_TABLE(); 
};

