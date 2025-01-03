
#ifndef _CORE_APP_H
#define _CORE_APP_H
#include <wx/wx.h>
#include <wx/bitmap.h>
#include <wx/filename.h>
#include <wx/dynlib.h>
#include "plugin.h"

#define APP_VERSION "v0.3.1"

extern struct tilecfg_t g_tilecfg;

class TileWindow;
class ConfigWindow;

class TileSolver
{

public: 
    TileSolver();
    bool LoadDecoder(wxFileName pluginfile);
    size_t Open(wxFileName infile = wxFileName()); // file -> m_filebuf
    int Decode(struct tilecfg_t *cfg, wxFileName pluginfile = wxFileName()); // m_filebuf -> m_tiles
    bool Render(); // m_tiles -> m_bitmap
    bool Save(wxFileName outfile = wxFileName()); // m_bitmap -> outfile
    bool Close();

    bool DecodeOk();
    bool RenderOk();

    struct tilecfg_t m_tilecfg;
    struct tile_decoder_t *m_decoder;
    wxDynamicLibrary m_cmodule;
    wxFileName m_infile, m_outfile;
    wxFileName m_pluginfile;
    wxMemoryBuffer m_filebuf;
    wxVector<wxImage> m_tiles; // use wxImage to store tiles, because wxBitmap hard to set pixel
    wxBitmap m_bitmap;

private:
    size_t PrepareTilebuf();
};

class MainApp : public wxApp
{
public:
    int SearchPlugins(wxString dirpath);
    bool Gui(wxString cmdstr = *wxEmptyString);
    bool Cli(wxString cmdstr = *wxEmptyString);

    // window
    TileWindow *m_tilewindow;
    ConfigWindow *m_configwindow;
    wxLogWindow *m_logwindow;
    
    // for solve tile
    int m_pluginindex;
    wxVector<wxFileName> m_pluginfiles; 
    TileSolver m_tilesolver;
    bool m_usegui;

private:    
    virtual bool OnInit() wxOVERRIDE;
    virtual void OnInitCmdLine(wxCmdLineParser& parser) wxOVERRIDE;
    virtual bool OnCmdLineParsed(wxCmdLineParser& parser) wxOVERRIDE;
};

wxDECLARE_APP(MainApp);
#endif