// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_TESTS_CEFSIMPLE_SIMPLE_HANDLER_H_
#define CEF_TESTS_CEFSIMPLE_SIMPLE_HANDLER_H_

#include "include/cef_client.h"
#include <list>
#include <map>

class BrowserClient : public CefClient,
                      public CefDisplayHandler,
                      public CefLifeSpanHandler,
                      public CefLoadHandler,
                      public CefRenderHandler
{
public:
  explicit BrowserClient(CefString url, int width, int height, CefString initialization_js, void *push_frame_, void *gst_cef);
  ~BrowserClient();

  // Provide access to the single global instance of this object.
  /* static BrowserClient* GetInstance(); */

  // CefClient methods:
  virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE { return this; }
  virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE { return this; }
  virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE { return this; }
  virtual CefRefPtr<CefRenderHandler> GetRenderHandler() OVERRIDE { return this; }

  // CefDisplayHandler methods:
  virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
                             const CefString &title) OVERRIDE;

  // CefLifeSpanHandler methods:
  virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
  virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
  virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

  // CefLoadHandler methods:
  // They will be called on the UI thread.
  virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefFrame> frame,
                           ErrorCode errorCode,
                           const CefString &errorText,
                           const CefString &failedUrl) OVERRIDE;

  virtual void OnLoadingStateChange(CefRefPtr<CefBrowser> browser,
                                    bool isLoading,
                                    bool canGoBack,
                                    bool canGoForward) OVERRIDE;

  virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser,
                         CefRefPtr<CefFrame> frame,
                         int httpStatusCode) OVERRIDE;

  bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect);
  void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType paintType,
               const RectList &rects, const void *buffer, int width, int height) OVERRIDE;

  // Request that all existing browser windows close.
  void CloseBrowser(void *gst_cef, bool force_close);
  void SetSize(void *gst_cef, int width, int height);
  void SetHidden(void *gst_cef, bool hidden);
  void ExecuteJS(void *gst_cef, char* js);
  void AddBrowserGstMap(CefRefPtr<CefBrowser> browser, void *gstCef, void *push_frame, int width, int height, char *initialization_js);

  bool IsClosing() const { return is_closing_; }
private:
  CefRefPtr<CefBrowser> browser_;
  bool is_closing_;
  void (* push_frame)(void *gstCef, const void *buffer, int width, int height);
  void *gst_cef_;

  bool ready_;
  int width_;
  int height_;
  std::string initialization_js_;

  void Refresh(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame);

  // Include the default reference counting implementation.
  IMPLEMENT_REFCOUNTING(BrowserClient);
};

#endif // CEF_TESTS_CEFSIMPLE_SIMPLE_HANDLER_H_
