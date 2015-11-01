//Copyright (C) 2015 Pedro Vicente
//GNU General Public License (GPL) Version 3 described in the LICENSE file 
#include "wx/wx.h"
#include "wx/splitter.h"
#include "wx/treectrl.h"
#include "wx/artprov.h"
#include "wx/imaglist.h"
#include "wx/grid.h"
#include "wx/mdi.h"
#include "wx/laywin.h"
#include "wx/filename.h"
#include "wx/filehistory.h"
#include "wx/config.h"
#include "wx/toolbar.h"
#include "icons/sample.xpm"
#include "icons/back.xpm"
#include "icons/forward.xpm"
#include "icons/doc_blue.xpm"
#include <algorithm>   
#include "netcdf.h" 

#define ID_WINDOW_SASH 100

//OPeNDAP
//http://www.esrl.noaa.gov/psd/thredds/dodsC/Datasets/cmap/enh/precip.mon.mean.nc

//Menu IDs
enum
{
  ID_OPENDAP = wxID_HIGHEST,
  ID_FORWARD,
  ID_BACK,
  ID_CHILD_QUIT
};

//utils
wxString GetPathComponent(const wxString &path);

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxTreeItemDataExplorer
/////////////////////////////////////////////////////////////////////////////////////////////////////

class wxTreeItemDataExplorer : public wxTreeItemData
{
public:
  enum ItemKind
  {
    Root,
    Group,
    Variable,
    Attribute
  };

  wxTreeItemDataExplorer(const wxString& file_name, const wxString& grp_nm_fll, const wxString& var_nm, ItemKind kind) :
    m_file_name(file_name),
    m_grp_nm_fll(grp_nm_fll),
    m_var_nm(var_nm),
    m_kind(kind)
  {

  }
  wxString m_file_name;  // file name
  wxString m_grp_nm_fll; // full name of group
  wxString m_var_nm;     // variable (or attribute) name
  ItemKind m_kind;       // type of item 
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxTreeCtrlExplorer
/////////////////////////////////////////////////////////////////////////////////////////////////////

class wxTreeCtrlExplorer : public wxTreeCtrl
{
public:
  wxTreeCtrlExplorer(wxWindow *parent, const wxWindowID id, const wxPoint& pos, const wxSize& size, long style);
  virtual ~wxTreeCtrlExplorer();
  void OnSelChanged(wxTreeEvent& event);
  void OnItemActivated(wxTreeEvent& event);

protected:
  void LoadItem(wxTreeItemDataExplorer *item);
  void* LoadVariable(const int nc_id, const int var_id, const nc_type var_type, size_t buf_sz);

private:
  wxDECLARE_EVENT_TABLE();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxFrameExplorer
/////////////////////////////////////////////////////////////////////////////////////////////////////

class wxFrameExplorer : public wxMDIParentFrame
{
public:
  wxFrameExplorer();
  ~wxFrameExplorer();
  void OnFileOpen(wxCommandEvent &event);
  void OnFileOpenDap(wxCommandEvent& event);
  void OnQuit(wxCommandEvent& event);
  void OnMRUFile(wxCommandEvent& event);
  void OnSize(wxSizeEvent& event);
  void OnSashDrag(wxSashEvent& event);
  void OnAbout(wxCommandEvent& event);
  int GetSashWidth()
  {
    wxRect rect = m_sash->GetRect();
    return rect.GetWidth();
  };

protected:
  int OpenFile(const wxString& file_name);
  int Iterate(const wxString& file_name, const int grp_id, wxTreeItemId item);
  wxTreeCtrlExplorer *m_tree;
  wxSashLayoutWindow *m_sash;
  wxTreeItemId m_tree_root;
  wxFileHistory m_file_history;

  //tree icons
  enum
  {
    id_folder,
    id_variable,
    id_attribute
  };

private:
  wxDECLARE_EVENT_TABLE();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxAppExplorer
/////////////////////////////////////////////////////////////////////////////////////////////////////

class wxAppExplorer : public wxApp
{
public:
  virtual bool OnInit();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxAppExplorer::OnInit
/////////////////////////////////////////////////////////////////////////////////////////////////////

bool wxAppExplorer::OnInit()
{
  wxFrameExplorer *frame = new wxFrameExplorer();
  frame->Show(true);
  frame->Maximize();
  return true;
}

DECLARE_APP(wxAppExplorer)
IMPLEMENT_APP(wxAppExplorer)

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxGridLayers
/////////////////////////////////////////////////////////////////////////////////////////////////////

class wxGridLayers : public wxGrid
{
public:
  wxGridLayers(wxWindow *parent,
    const wxSize& size,
    int nbr_rows,
    int nbr_cols,
    nc_type var_type,
    void *data);
  ~wxGridLayers();
  void ShowGrid();

protected:
  int m_nbr_rows;
  int m_nbr_cols;
  nc_type m_var_type;
  void *m_data;

private:
  DECLARE_EVENT_TABLE()
};

wxBEGIN_EVENT_TABLE(wxGridLayers, wxGrid)
wxEND_EVENT_TABLE()

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxGridLayers::wxGridLayers
//store data buffer to handle 3D cases 
/////////////////////////////////////////////////////////////////////////////////////////////////////

wxGridLayers::wxGridLayers(wxWindow *parent, const wxSize& size, int nbr_rows, int nbr_cols, nc_type var_type, void *data) :
wxGrid(parent, wxID_ANY, wxPoint(0, 0), size, wxNO_BORDER),
m_nbr_rows(nbr_rows),
m_nbr_cols(nbr_cols),
m_var_type(var_type),
m_data(data)
{
  this->CreateGrid(m_nbr_rows, m_nbr_cols);
  for (int idx_col = 0; idx_col < m_nbr_cols; idx_col++)
  {
    this->SetColLabelValue(idx_col, wxString::Format(wxT("%d"), idx_col + 1));
  }
  //show data
  this->ShowGrid();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxGridLayers::~wxGridLayers
/////////////////////////////////////////////////////////////////////////////////////////////////////

wxGridLayers::~wxGridLayers()
{
  free(m_data);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxFrameChild
/////////////////////////////////////////////////////////////////////////////////////////////////////

class wxFrameChild : public wxFrame
{
public:
  wxFrameChild(wxMDIParentFrame *parent,
    const wxString& title,
    int nbr_rows,
    int nbr_cols,
    int nbr_layers,
    nc_type var_type,
    void *data);
  void OnQuit(wxCommandEvent& event);
  void OnActivate(wxActivateEvent& event);
  void OnForward(wxCommandEvent& event);
  void OnUpdateForward(wxUpdateUIEvent& event);
  void OnBack(wxCommandEvent& event);
  void OnUpdateBack(wxUpdateUIEvent& event);
  void InitToolBar(wxToolBar* tb);

protected:
  wxGridLayers *m_grid;
  int m_nbr_layers; // numbers of layers
  int m_layer;      // current layer 

public:
  int GetLayer() { return m_layer; };

private:
  DECLARE_EVENT_TABLE()
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxFrameChild::wxFrameChild
/////////////////////////////////////////////////////////////////////////////////////////////////////

wxBEGIN_EVENT_TABLE(wxFrameChild, wxFrame)
EVT_MENU(ID_CHILD_QUIT, wxFrameChild::OnQuit)
EVT_MENU(ID_FORWARD, wxFrameChild::OnForward)
EVT_UPDATE_UI(ID_FORWARD, wxFrameChild::OnUpdateForward)
EVT_MENU(ID_BACK, wxFrameChild::OnBack)
EVT_UPDATE_UI(ID_BACK, wxFrameChild::OnUpdateBack)
wxEND_EVENT_TABLE()

wxFrameChild::wxFrameChild(wxMDIParentFrame *parent, const wxString& title, int nbr_rows, int nbr_cols, int nbr_layers, nc_type var_type, void *data) :
wxFrame(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize,
wxDEFAULT_FRAME_STYLE | wxNO_FULL_REPAINT_ON_RESIZE | wxFRAME_FLOAT_ON_PARENT),
m_nbr_layers(nbr_layers),
m_layer(0)
{
  SetIcon(wxICON(sample));
  m_grid = new wxGridLayers(this, GetClientSize(), nbr_rows, nbr_cols, var_type, data);
  CreateToolBar(wxNO_BORDER | wxTB_FLAT | wxTB_HORIZONTAL);
  InitToolBar(GetToolBar());
  Raise();
  //nicely rearranje children under parent frame
  wxPoint pos = GetPosition();
  wxFrameExplorer *frame = (wxFrameExplorer*)GetParent();
  pos.x += frame->GetSashWidth();
  SetPosition(pos);
  //set size accordingly to grid
  wxSize size((nbr_cols + 1) * m_grid->GetDefaultColSize() + 10, (nbr_rows + 1) * m_grid->GetDefaultRowSize() + GetToolBar()->GetSize().GetHeight());
  this->SetClientSize(std::max(GetClientSize().GetWidth(), size.GetWidth()), std::max(GetClientSize().GetHeight(), size.GetHeight()));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxFrameChild::InitToolBar
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wxFrameChild::InitToolBar(wxToolBar* tb)
{
  tb->AddTool(ID_FORWARD, wxT("Forward"), wxBitmap(forward_xpm), wxT("Move forward to next layer."));
  tb->AddTool(ID_BACK, wxT("Back"), wxBitmap(back_xpm), wxT("Return to previous layer."));
  tb->Realize();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxFrameChild::OnQuit
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wxFrameChild::OnQuit(wxCommandEvent& WXUNUSED(event))
{
  Close(true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//wxFrameChild::OnForward
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wxFrameChild::OnForward(wxCommandEvent& WXUNUSED(event))
{
  m_layer++;
  if (m_layer >= m_nbr_layers)
  {
    m_layer = m_nbr_layers - 1;
    return;
  }
  m_grid->ShowGrid();
  m_grid->Refresh();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//wxFrameChild::OnUpdateForward
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wxFrameChild::OnUpdateForward(wxUpdateUIEvent& event)
{
  (m_nbr_layers > 1) ? event.Enable(1) : event.Enable(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//wxFrameChild::OnBack
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wxFrameChild::OnBack(wxCommandEvent& WXUNUSED(event))
{
  m_layer--;
  if (m_layer < 0)
  {
    m_layer = 0;
    return;
  }
  m_grid->ShowGrid();
  m_grid->Refresh();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//wxFrameChild::OnUpdateBack
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wxFrameChild::OnUpdateBack(wxUpdateUIEvent& event)
{
  (m_nbr_layers > 1) ? event.Enable(1) : event.Enable(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxFrameChild::OnActivate
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wxFrameChild::OnActivate(wxActivateEvent& event)
{
  if (event.GetActive() && m_grid)
    m_grid->SetFocus();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxFrameExplorer::wxFrameExplorer
/////////////////////////////////////////////////////////////////////////////////////////////////////

wxBEGIN_EVENT_TABLE(wxFrameExplorer, wxMDIParentFrame)
EVT_MENU(wxID_OPEN, wxFrameExplorer::OnFileOpen)
EVT_MENU(ID_OPENDAP, wxFrameExplorer::OnFileOpenDap)
EVT_MENU(wxID_EXIT, wxFrameExplorer::OnQuit)
EVT_MENU_RANGE(wxID_FILE1, wxID_FILE9, wxFrameExplorer::OnMRUFile)
EVT_SIZE(wxFrameExplorer::OnSize)
EVT_SASH_DRAGGED_RANGE(ID_WINDOW_SASH, ID_WINDOW_SASH, wxFrameExplorer::OnSashDrag)
EVT_MENU(wxID_ABOUT, wxFrameExplorer::OnAbout)
wxEND_EVENT_TABLE()

wxFrameExplorer::wxFrameExplorer() : wxMDIParentFrame(NULL, wxID_ANY, wxT("netCDF Explorer"),
wxDefaultPosition, wxSize(550, 840))
{
  int w, h;

  SetIcon(wxICON(sample));
  wxMenu *menu_file = new wxMenu;
  menu_file->Append(wxID_OPEN, _("&Open...\tCtrl+O"));
  menu_file->Append(ID_OPENDAP, wxT("OPeN&DAP...\tCtrl+D"));
  menu_file->AppendSeparator();
  menu_file->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit");
  wxMenu *menu_help = new wxMenu;
  menu_help->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");
  wxMenuBar *menu_bar = new wxMenuBar();
  menu_bar->Append(menu_file, "&File");
  menu_bar->Append(menu_help, "&Help");
  SetMenuBar(menu_bar);
  m_file_history.UseMenu(menu_file);
  m_file_history.AddFilesToMenu(menu_file);
  m_file_history.Load(*wxConfig::Get());
  CreateStatusBar(1);

  GetClientSize(&w, &h);
  wxSashLayoutWindow* win;
  win = new wxSashLayoutWindow(this, ID_WINDOW_SASH, wxDefaultPosition, wxDefaultSize, wxNO_BORDER | wxSW_3D | wxCLIP_CHILDREN);
  win->SetDefaultSize(wxSize(300, h));
  win->SetOrientation(wxLAYOUT_VERTICAL);
  win->SetAlignment(wxLAYOUT_LEFT);
  win->SetSashVisible(wxSASH_RIGHT, true);
  win->SetExtraBorderSize(10);
  win->SetMinimumSizeX(100);
  win->SetBackgroundColour(*wxWHITE);
  m_sash = win;

  m_tree = new wxTreeCtrlExplorer(m_sash, wxID_ANY, wxPoint(0, 0), wxSize(160, 250), wxTR_DEFAULT_STYLE | wxNO_BORDER | wxTR_HIDE_ROOT);
  wxImageList* imglist = new wxImageList(16, 16, true, 2);
  wxBitmap bitmaps[3];
  bitmaps[id_folder] = wxBitmap(wxArtProvider::GetBitmap(wxART_FOLDER, wxART_OTHER, wxSize(16, 16)));
  bitmaps[id_variable] = wxBitmap(wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16, 16)));
  bitmaps[id_attribute] = wxBitmap(doc_blue_xpm);
  imglist->Add(bitmaps[id_folder]);
  imglist->Add(bitmaps[id_variable]);
  imglist->Add(bitmaps[id_attribute]);
  m_tree->AssignImageList(imglist);
  m_tree_root = m_tree->AddRoot("");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxFrameExplorer::~wxFrameExplorer
/////////////////////////////////////////////////////////////////////////////////////////////////////

wxFrameExplorer::~wxFrameExplorer()
{
  m_file_history.Save(*wxConfig::Get());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxFrameExplorer::OnQuit
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wxFrameExplorer::OnQuit(wxCommandEvent& WXUNUSED(event))
{
  m_file_history.Save(*wxConfig::Get());
  Close(true);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxFrameExplorer::OnMRUFile
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wxFrameExplorer::OnMRUFile(wxCommandEvent& event)
{
  wxString path(m_file_history.GetHistoryFile(event.GetId() - wxID_FILE1));
  if (!path.empty())
  {
    OpenFile(path);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxFrameExplorer::OnFileOpen
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wxFrameExplorer::OnFileOpen(wxCommandEvent &WXUNUSED(event))
{
  wxString path;
  wxFileDialog dlg(this, wxT("Open file"),
    wxEmptyString,
    wxEmptyString,
    wxString::Format
    (
    wxT("netCDF (*.nc)|*.nc|All files (%s)|%s"),
    wxFileSelectorDefaultWildcardStr,
    wxFileSelectorDefaultWildcardStr
    ),
    wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_CHANGE_DIR);
  if (dlg.ShowModal() != wxID_OK) return;
  path = dlg.GetPath();
  if (this->OpenFile(path) != NC_NOERR)
  {

  }
  m_file_history.AddFileToHistory(path);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxFrameExplorer::OnFileOpenDap
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wxFrameExplorer::OnFileOpenDap(wxCommandEvent& WXUNUSED(event))
{
  wxTextEntryDialog dialog(this, wxT("OPeNDAP URL:"), wxT("OPeNDAP"));
  if (dialog.ShowModal() == wxID_OK)
  {
    wxString path = dialog.GetValue();
    if (this->OpenFile(path) != NC_NOERR)
    {

    }
    m_file_history.AddFileToHistory(path);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxFrameExplorer::OnSashDrag
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wxFrameExplorer::OnSashDrag(wxSashEvent& event)
{
  int w, h;
  GetClientSize(&w, &h);

  if (event.GetDragStatus() == wxSASH_STATUS_OUT_OF_RANGE)
    return;

  switch (event.GetId())
  {
  case ID_WINDOW_SASH:
    m_sash->SetDefaultSize(wxSize(event.GetDragRect().width, h));
    break;
  }

  wxLayoutAlgorithm layout;
  layout.LayoutMDIFrame(this);
  GetClientWindow()->Refresh();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxFrameExplorer::OnSize
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wxFrameExplorer::OnSize(wxSizeEvent& WXUNUSED(event))
{
  wxLayoutAlgorithm layout;
  layout.LayoutMDIFrame(this);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxFrameExplorer::OpenFile
/////////////////////////////////////////////////////////////////////////////////////////////////////

int wxFrameExplorer::OpenFile(const wxString& file_name)
{
  int nc_id;

  if (nc_open(file_name, NC_NOWRITE, &nc_id) != NC_NOERR)
  {
    return -1;
  }

  wxTreeItemDataExplorer *item_data = new wxTreeItemDataExplorer(file_name, file_name, "/", wxTreeItemDataExplorer::Root);
  //last component of full path file name used for root tree only
  wxTreeItemId root = m_tree->AppendItem(m_tree_root, GetPathComponent(file_name), 0, 0, item_data);

  if (Iterate(file_name, nc_id, root) != NC_NOERR)
  {

  }

  if (nc_close(nc_id) != NC_NOERR)
  {

  }

  return NC_NOERR;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxFrameExplorer::Iterate
/////////////////////////////////////////////////////////////////////////////////////////////////////

int wxFrameExplorer::Iterate(const wxString& file_name, const int grp_id, wxTreeItemId item)
{
  char grp_nm[NC_MAX_NAME + 1]; // group name 
  char var_nm[NC_MAX_NAME + 1]; // variable name 
  char *grp_nm_fll = NULL; // group full name 
  int nbr_att; // number of attributes 
  int nbr_dmn; // number of dimensions 
  int nbr_var; // number of variables 
  int nbr_grp; // number of sub-groups in this group 
  int nbr_dmn_var; // number of dimensions for variable 
  nc_type var_typ; // netCDF type 
  int *grp_ids; // sub-group IDs array
  size_t grp_nm_lng; //lenght of full group name

  // get full name of group
  if (nc_inq_grpname_full(grp_id, &grp_nm_lng, NULL) != NC_NOERR)
  {

  }

  grp_nm_fll = new char[grp_nm_lng + 1];

  if (nc_inq_grpname_full(grp_id, &grp_nm_lng, grp_nm_fll) != NC_NOERR)
  {

  }

  if (nc_inq(grp_id, &nbr_dmn, &nbr_var, &nbr_att, (int *)NULL) != NC_NOERR)
  {

  }

  for (int idx_var = 0; idx_var < nbr_var; idx_var++)
  {
    if (nc_inq_var(grp_id, idx_var, var_nm, &var_typ, &nbr_dmn_var, (int *)NULL, &nbr_att) != NC_NOERR)
    {

    }

    wxTreeItemDataExplorer *item_data = new wxTreeItemDataExplorer(file_name, grp_nm_fll, var_nm, wxTreeItemDataExplorer::Variable);
    m_tree->AppendItem(item, var_nm, 1, 1, item_data);
  }

  if (nc_inq_grps(grp_id, &nbr_grp, (int *)NULL) != NC_NOERR)
  {

  }

  grp_ids = new int[nbr_grp];

  if (nc_inq_grps(grp_id, &nbr_grp, grp_ids) != NC_NOERR)
  {

  }

  for (int idx_grp = 0; idx_grp < nbr_grp; idx_grp++)
  {
    if (nc_inq_grpname(grp_ids[idx_grp], grp_nm) != NC_NOERR)
    {

    }

    wxTreeItemDataExplorer *item_data = new wxTreeItemDataExplorer(file_name, grp_nm_fll, grp_nm, wxTreeItemDataExplorer::Group);
    wxTreeItemId sub_item = m_tree->AppendItem(item, grp_nm, 0, 0, item_data);

    if (Iterate(file_name, grp_ids[idx_grp], sub_item) != NC_NOERR)
    {

    }
  }

  delete[] grp_ids;
  delete[] grp_nm_fll;

  return NC_NOERR;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxTreeCtrlExplorer::wxTreeCtrlExplorer
/////////////////////////////////////////////////////////////////////////////////////////////////////

wxBEGIN_EVENT_TABLE(wxTreeCtrlExplorer, wxTreeCtrl)
EVT_TREE_SEL_CHANGED(wxID_ANY, wxTreeCtrlExplorer::OnSelChanged)
EVT_TREE_ITEM_ACTIVATED(wxID_ANY, wxTreeCtrlExplorer::OnItemActivated)
wxEND_EVENT_TABLE()

wxTreeCtrlExplorer::wxTreeCtrlExplorer(wxWindow *parent, const wxWindowID id, const wxPoint& pos, const wxSize& size, long style)
: wxTreeCtrl(parent, id, pos, size, style)
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxTreeCtrlExplorer::~wxTreeCtrlExplorer
/////////////////////////////////////////////////////////////////////////////////////////////////////

wxTreeCtrlExplorer::~wxTreeCtrlExplorer()
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxTreeCtrlExplorer::OnSelChanged
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wxTreeCtrlExplorer::OnSelChanged(wxTreeEvent& event)
{
  event.Skip();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxTreeCtrlExplorer::OnItemActivated
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wxTreeCtrlExplorer::OnItemActivated(wxTreeEvent& event)
{
  wxTreeItemId item_id = event.GetItem();
  wxTreeItemDataExplorer *item = (wxTreeItemDataExplorer *)GetItemData(item_id);
  event.Skip();
  if (item->m_kind != wxTreeItemDataExplorer::Variable)
  {
    return;
  }
  LoadItem(item);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxTreeCtrlExplorer::LoadItem
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wxTreeCtrlExplorer::LoadItem(wxTreeItemDataExplorer *item)
{
  char var_nm[NC_MAX_NAME + 1]; // variable name 
  int nc_id;
  int grp_id;
  int var_id;
  nc_type var_type = -1;
  int nbr_dmn;
  int var_dimid[NC_MAX_VAR_DIMS];
  size_t dmn_sz[NC_MAX_VAR_DIMS];
  size_t buf_sz; // variable size
  int fl_fmt;
  void *buf = NULL;
  int nbr_rows = 0;
  int nbr_cols = 0;
  int nbr_layers = 0;

  //get parent
  wxSashLayoutWindow *sash = (wxSashLayoutWindow*)GetParent();
  wxFrameExplorer *frame = (wxFrameExplorer*)sash->GetParent();

  if (item->m_kind != wxTreeItemDataExplorer::Variable)
  {
    return;
  }

  if (nc_open(item->m_file_name, NC_NOWRITE, &nc_id) != NC_NOERR)
  {

  }

  //need a file format inquiry, since nc_inq_grp_full_ncid does not handle netCDF3 cases
  if (nc_inq_format(nc_id, &fl_fmt) != NC_NOERR)
  {

  }

  if (fl_fmt == NC_FORMAT_NETCDF4 || fl_fmt == NC_FORMAT_NETCDF4_CLASSIC)
  {
    // obtain group ID for netCDF4 files
    if (nc_inq_grp_full_ncid(nc_id, item->m_grp_nm_fll, &grp_id) != NC_NOERR)
    {

    }
  }
  else
  {
    //make the group ID the file ID for netCDF3 cases
    grp_id = nc_id;
  }

  //all hunky dory from here 

  // get variable ID
  if (nc_inq_varid(grp_id, item->m_var_nm, &var_id) != NC_NOERR)
  {

  }

  if (nc_inq_var(grp_id, var_id, var_nm, &var_type, &nbr_dmn, var_dimid, (int *)NULL) != NC_NOERR)
  {

  }

  //get dimensions
  for (int idx_dmn = 0; idx_dmn < nbr_dmn; idx_dmn++)
  {
    //dimensions belong to groups
    if (nc_inq_dimlen(grp_id, var_dimid[idx_dmn], &dmn_sz[idx_dmn]) != NC_NOERR)
    {

    }
  }


  //define grid
  if (nbr_dmn == 0)
  {
    nbr_rows = 1;
    nbr_cols = 1;
    nbr_layers = 1;
  }
  else if (nbr_dmn == 1)
  {
    nbr_rows = dmn_sz[0];
    nbr_cols = 1;
    nbr_layers = 1;
  }
  else if (nbr_dmn == 2)
  {
    nbr_rows = dmn_sz[0];
    nbr_cols = dmn_sz[1];
    nbr_layers = 1;
  }
  else if (nbr_dmn >= 3)
  {
    nbr_rows = dmn_sz[1];
    nbr_cols = dmn_sz[2];
    nbr_layers = dmn_sz[0];
  }

  //define buffer size
  buf_sz = 1;
  for (int idx_dmn = 0; idx_dmn < nbr_dmn; idx_dmn++)
  {
    buf_sz *= dmn_sz[idx_dmn];
  }

  //allocate buffer
  buf = LoadVariable(grp_id, var_id, var_type, buf_sz);

  //show
  wxFrameChild *subframe = new wxFrameChild(frame,
    wxString::Format(wxT("%s : %s"), GetPathComponent(item->m_file_name), item->m_var_nm),
    nbr_rows,
    nbr_cols,
    nbr_layers,
    var_type,
    buf);
  subframe->Show(true);

  if (nc_close(nc_id) != NC_NOERR)
  {

  }

}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxTreeCtrlExplorer::LoadVariable
/////////////////////////////////////////////////////////////////////////////////////////////////////

void* wxTreeCtrlExplorer::LoadVariable(const int nc_id, const int var_id, const nc_type var_type, size_t buf_sz)
{
  void *buf = NULL;
  switch (var_type)
  {
  case NC_FLOAT:
    buf = malloc(buf_sz * sizeof(float));
    if (nc_get_var_float(nc_id, var_id, static_cast<float *>(buf)) != NC_NOERR)
    {
    }
    break;
  case NC_DOUBLE:
    buf = malloc(buf_sz * sizeof(double));
    if (nc_get_var_double(nc_id, var_id, static_cast<double *>(buf)) != NC_NOERR)
    {
    }
    break;
  case NC_INT:
    buf = malloc(buf_sz * sizeof(int));
    if (nc_get_var_int(nc_id, var_id, static_cast<int *>(buf)) != NC_NOERR)
    {
    }
    break;
  case NC_SHORT:
    buf = malloc(buf_sz * sizeof(short));
    if (nc_get_var_short(nc_id, var_id, static_cast<short *>(buf)) != NC_NOERR)
    {
    }
    break;
  case NC_CHAR:
    buf = malloc(buf_sz * sizeof(char));
    if (nc_get_var_text(nc_id, var_id, static_cast<char *>(buf)) != NC_NOERR)
    {
    }
    break;
  case NC_BYTE:
    buf = malloc(buf_sz * sizeof(signed char));
    if (nc_get_var_schar(nc_id, var_id, static_cast<signed char *>(buf)) != NC_NOERR)
    {
    }
    break;
  case NC_UBYTE:
    buf = malloc(buf_sz * sizeof(unsigned char));
    if (nc_get_var_uchar(nc_id, var_id, static_cast<unsigned char *>(buf)) != NC_NOERR)
    {
    }
    break;
  case NC_USHORT:
    buf = malloc(buf_sz * sizeof(unsigned short));
    if (nc_get_var_ushort(nc_id, var_id, static_cast<unsigned short *>(buf)) != NC_NOERR)
    {
    }
    break;
  case NC_UINT:
    buf = malloc(buf_sz * sizeof(unsigned int));
    if (nc_get_var_uint(nc_id, var_id, static_cast<unsigned int *>(buf)) != NC_NOERR)
    {
    }
    break;
  case NC_INT64:
    buf = malloc(buf_sz * sizeof(long long));
    if (nc_get_var_longlong(nc_id, var_id, static_cast<long long *>(buf)) != NC_NOERR)
    {
    }
    break;
  case NC_UINT64:
    buf = malloc(buf_sz * sizeof(unsigned long long));
    if (nc_get_var_ulonglong(nc_id, var_id, static_cast<unsigned long long *>(buf)) != NC_NOERR)
    {
    }
    break;
  case NC_STRING:
    buf = malloc(buf_sz * sizeof(char*));
    if (nc_get_var_string(nc_id, var_id, static_cast<char* *>(buf)) != NC_NOERR)
    {
    }
    break;
  }
  return buf;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxGridLayers::ShowGrid
/////////////////////////////////////////////////////////////////////////////////////////////////////


void wxGridLayers::ShowGrid()
{
  //handle 3D cases
  wxFrameChild *parent = (wxFrameChild*)GetParent();
  size_t idx_buf = parent->GetLayer() * m_nbr_rows * m_nbr_cols;
  float *buf_float = NULL;
  double *buf_double = NULL;
  int *buf_int = NULL;
  short *buf_short = NULL;
  char *buf_char = NULL;
  signed char *buf_byte = NULL;
  unsigned char *buf_ubyte = NULL;
  unsigned short *buf_ushort = NULL;
  unsigned int *buf_uint = NULL;
  long long *buf_int64 = NULL;
  unsigned long long *buf_uint64 = NULL;
  char* *buf_string = NULL;

  switch (m_var_type)
  {
  case NC_FLOAT:
    buf_float = static_cast<float*> (m_data);
    for (int idx_row = 0; idx_row < m_nbr_rows; idx_row++)
    {
      for (int idx_col = 0; idx_col < m_nbr_cols; idx_col++)
      {
        this->SetCellValue(idx_row, idx_col, wxString::Format(wxT("%g"), buf_float[idx_buf]));
        idx_buf++;
      }
    }
    break;
  case NC_DOUBLE:
    buf_double = static_cast<double*> (m_data);
    for (int idx_row = 0; idx_row < m_nbr_rows; idx_row++)
    {
      for (int idx_col = 0; idx_col < m_nbr_cols; idx_col++)
      {
        this->SetCellValue(idx_row, idx_col, wxString::Format(wxT("%.12g"), buf_double[idx_buf]));
        idx_buf++;
      }
    }
    break;
  case NC_INT:
    buf_int = static_cast<int*> (m_data);
    for (int idx_row = 0; idx_row < m_nbr_rows; idx_row++)
    {
      for (int idx_col = 0; idx_col < m_nbr_cols; idx_col++)
      {
        this->SetCellValue(idx_row, idx_col, wxString::Format(wxT("%d"), buf_int[idx_buf]));
        idx_buf++;
      }
    }
    break;
  case NC_SHORT:
    buf_short = static_cast<short*> (m_data);
    for (int idx_row = 0; idx_row < m_nbr_rows; idx_row++)
    {
      for (int idx_col = 0; idx_col < m_nbr_cols; idx_col++)
      {
        this->SetCellValue(idx_row, idx_col, wxString::Format(wxT("%d"), buf_short[idx_buf]));
        idx_buf++;
      }
    }
    break;
  case NC_CHAR:
    buf_char = static_cast<char*> (m_data);
    for (int idx_row = 0; idx_row < m_nbr_rows; idx_row++)
    {
      for (int idx_col = 0; idx_col < m_nbr_cols; idx_col++)
      {
        this->SetCellValue(idx_row, idx_col, wxString::Format(wxT("%c"), buf_char[idx_buf]));
        idx_buf++;
      }
    }
    break;
  case NC_BYTE:
    buf_byte = static_cast<signed char*> (m_data);
    for (int idx_row = 0; idx_row < m_nbr_rows; idx_row++)
    {
      for (int idx_col = 0; idx_col < m_nbr_cols; idx_col++)
      {
        this->SetCellValue(idx_row, idx_col, wxString::Format(wxT("%d"), buf_byte[idx_buf]));
        idx_buf++;
      }
    }
    break;
  case NC_UBYTE:
    buf_ubyte = static_cast<unsigned char*> (m_data);
    for (int idx_row = 0; idx_row < m_nbr_rows; idx_row++)
    {
      for (int idx_col = 0; idx_col < m_nbr_cols; idx_col++)
      {
        this->SetCellValue(idx_row, idx_col, wxString::Format(wxT("%d"), buf_ubyte[idx_buf]));
        idx_buf++;
      }
    }
    break;
  case NC_USHORT:
    buf_ushort = static_cast<unsigned short*> (m_data);
    for (int idx_row = 0; idx_row < m_nbr_rows; idx_row++)
    {
      for (int idx_col = 0; idx_col < m_nbr_cols; idx_col++)
      {
        this->SetCellValue(idx_row, idx_col, wxString::Format(wxT("%d"), buf_ushort[idx_buf]));
        idx_buf++;
      }
    }
    break;
  case NC_UINT:
    buf_uint = static_cast<unsigned int*> (m_data);
    for (int idx_row = 0; idx_row < m_nbr_rows; idx_row++)
    {
      for (int idx_col = 0; idx_col < m_nbr_cols; idx_col++)
      {
        this->SetCellValue(idx_row, idx_col, wxString::Format(wxT("%d"), buf_uint[idx_buf]));
        idx_buf++;
      }
    }
    break;
  case NC_INT64:
    buf_int64 = static_cast<long long*> (m_data);
    for (int idx_row = 0; idx_row < m_nbr_rows; idx_row++)
    {
      for (int idx_col = 0; idx_col < m_nbr_cols; idx_col++)
      {
        this->SetCellValue(idx_row, idx_col, wxString::Format(wxT("%lld"), buf_int64[idx_buf]));
        idx_buf++;
      }
    }
    break;
  case NC_UINT64:
    buf_uint64 = static_cast<unsigned long long*> (m_data);
    for (int idx_row = 0; idx_row < m_nbr_rows; idx_row++)
    {
      for (int idx_col = 0; idx_col < m_nbr_cols; idx_col++)
      {
        this->SetCellValue(idx_row, idx_col, wxString::Format(wxT("%llu"), buf_uint64[idx_buf]));
        idx_buf++;
      }
    }
    break;
  case NC_STRING:
    buf_string = static_cast<char**> (m_data);
    for (int idx_row = 0; idx_row < m_nbr_rows; idx_row++)
    {
      for (int idx_col = 0; idx_col < m_nbr_cols; idx_col++)
      {
        this->SetCellValue(idx_row, idx_col, wxString::Format(wxT("%s"), buf_string[idx_buf]));
        idx_buf++;
      }
    }
    break;
  }//switch
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//wxFrameExplorer::OnAbout
/////////////////////////////////////////////////////////////////////////////////////////////////////

void wxFrameExplorer::OnAbout(wxCommandEvent& WXUNUSED(event))
{
  wxMessageBox(wxString::Format
    (
    "netCDF Explorer 1.0\n"
    "(c) 2015 Pedro Vicente -- Space Research Software LLC\n\n"
    "%s.",
    wxGetOsDescription()
    ),
    "netCDF Explorer",
    wxOK,
    this);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//GetPathComponent
/////////////////////////////////////////////////////////////////////////////////////////////////////

wxString GetPathComponent(const wxString &path)
{
  wxString name;
  bool isurl = (path.SubString(0, 3) == "http");
  if (isurl)
  {
    return path;
  }
  else
  {
#ifdef __WINDOWS__
    name = path.AfterLast('\\');
#else
    name = path.AfterLast('/');
#endif
  }
  return name;
}
