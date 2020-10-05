#include "ScreenshotTimer.h"
#include <cstdio>
#include <cmath>
#include <wx/dcclient.h>
#include <wx/colour.h>
#include <wx/pen.h>

ScreenshotTimer::ScreenshotTimer(wxWindow* dev_ctx, std::shared_ptr<Model>& model)
	: m_dev_ctx(dev_ctx)
{
	m_model = model;

	MSS::Rect rect;
	rect.width = 322;
	rect.height = 455;
	rect.left = 677;
	rect.top = 289;

	m_image_data = std::vector<ScreenshotTimer::RGB>(rect.height * rect.width);
	m_mss = std::make_unique<MSS>(rect);

	m_image = new wxImage(
		rect.width, rect.height,
		reinterpret_cast<uint8_t*>(m_image_data.data()), false);

	
}

void ScreenshotTimer::Notify() 
{
	m_mss->grab();
	auto& src_data = m_mss->get_data();
	auto& dest_data = m_image_data;

	for (int i = 0, N = src_data.size(); i < N; i++) {
		dest_data[i].R = src_data[i].B;
		dest_data[i].G = src_data[i].G;
		dest_data[i].B = src_data[i].R;
	}

	const auto& rect = m_mss->get_rect();

	auto pred = m_model->resize_and_predict(
		reinterpret_cast<uint8_t*>(dest_data.data()),
		rect.width, rect.height, 3);
	
	wxBitmap bmp(*m_image);
	wxClientDC dc(m_dev_ctx);

	wxColor color(0, 0, 255);
	wxPen pen(color, 1, wxPENSTYLE_SOLID);
	pen.SetWidth(3);
	wxBrush brush(color, wxBRUSHSTYLE_TRANSPARENT);

	dc.DrawBitmap(bmp, 0, 0, false);

	if (pred.confidence > 0.8) {
		const int bw = static_cast<int>(0.27f * rect.width);
		const int bh = static_cast<int>(0.18f * rect.height);

		int x = static_cast<int>(pred.x * rect.width);
		int y = static_cast<int>(pred.y * rect.height);

		int p1 = std::max(x - bw / 2, 0); 
		int p2 = std::min(x + bw / 2, rect.width);
		int p3 = std::max(y - bh / 2, 0);
		int p4 = std::min(y + bh / 2, rect.height);

		
		dc.SetPen(pen);
		dc.SetBrush(brush);
		dc.DrawRectangle(p1, p3, p2-p1, p4-p3);
	}

	

	

	
}
