#include "GrandPrixRecommender.h"
#include "dataInit.h"

class Application : public wxApp
{
public:
    virtual bool OnInit();
};

class MainWindow : public wxFrame
{
public:
    MainWindow();

private:
    void OnAdd(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
};

wxIMPLEMENT_APP(Application);

bool Application::OnInit()
{
    MainWindow* frame = new MainWindow();
    frame->Show(true);
    DataInit data;
    data.initializeData();
    std::string testCirc = data.getCircuits()[0].name;
    std::string testCons = data.getConstructors()[0].name;
    std::string testDriv = data.getDrivers()[0].forename + " " + data.getDrivers()[0].surname;
    wxMessageBox(testCirc + "\n" + testCons + "\n" + testDriv, "Test box");
    return true;
}

MainWindow::MainWindow()
    : wxFrame(NULL, wxID_ANY, "Grand Prix Recommender")
{
   // Create menu bar
    wxMenuBar* menuBar = new wxMenuBar;

    // Add menus
    wxMenu* programMenu = new wxMenu;
    wxMenu* settingsMenu = new wxMenu;
    
    // Define program menu
    programMenu->Append(wxID_ADD, "&Add", "Add new user to recommender");
    programMenu->AppendSeparator();
    programMenu->Append(wxID_EXIT, "&Quit", "Close program");

    // Append program menu
    menuBar->Append(programMenu, "&Program");

    // Append menu bar to frame
    SetMenuBar(menuBar);

    Bind(wxEVT_MENU, &MainWindow::OnAdd, this, wxID_ADD);
    Bind(wxEVT_MENU, &MainWindow::OnExit, this, wxID_EXIT);
}

void MainWindow::OnExit(wxCommandEvent& event){
    Close(true);
}

void MainWindow::OnAdd(wxCommandEvent& event){
    wxMessageBox("Add user clicked", "Information");
}