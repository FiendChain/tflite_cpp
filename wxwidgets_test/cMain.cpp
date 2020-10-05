#include "cMain.h"

#include <string>
#include <filesystem>

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_CLOSE(cMain::onClose)
wxEND_EVENT_TABLE()

namespace fs = std::filesystem;

cMain::cMain()
: wxFrame(nullptr, wxID_ANY, "Test title")
{
    const std::string filepath_str = "./cnn_113_80_quantized.tflite";
    const fs::path filepath = filepath_str;
    const fs::path abs_filepath = fs::absolute(filepath);

    m_model = std::make_shared<Model>(abs_filepath.string().c_str());

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

