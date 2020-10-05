#pragma once

#include <wx/timer.h>
#include <wx/dc.h>
#include <wx/image.h>
#include <wx/bitmap.h>
#include <memory>

#include "MSS.h"
#include "Model.h"

class ScreenshotTimer: public wxTimer 
{
private:
	typedef struct {
		uint8_t R, G, B;
	} RGB;
private:
	wxWindow* m_dev_ctx;
	wxImage* m_image;
	std::vector<RGB> m_image_data;
	std::unique_ptr<MSS> m_mss;
	std::shared_ptr<Model> m_model;
public:
	ScreenshotTimer(wxWindow* dev_ctx, std::shared_ptr<Model>& model);
	virtual void Notify();
};
