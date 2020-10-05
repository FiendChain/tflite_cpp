#include "cMain.h"
#include <iostream>

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
    EVT_CLOSE(cMain::onClose)
wxEND_EVENT_TABLE()

cMain::cMain()
: wxFrame(nullptr, wxID_ANY, "Test title")
{
    const char* DEFAULT_FILEPATH = "C:/Users/acidi/Coding/Projects/SoccerBot/assets/models/cnn_113_80_quantized.tflite";
    m_model = std::make_shared<Model>(DEFAULT_FILEPATH);
    m_model->show_info();

    m_screenshot_timer = std::make_unique<ScreenshotTimer>(this, m_model);
    Show();
    m_screenshot_timer->Start(16);
}

cMain::~cMain()
{
    
}

void cMain::onClose(wxCloseEvent& evt)
{
    m_screenshot_timer->Stop();
    evt.Skip();
}

