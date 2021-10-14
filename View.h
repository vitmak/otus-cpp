#pragma once

#include <string>
#include <vector>
#include <functional>


enum class PrimitiveTypes {
	ePoint = 0,
	eLine,
	eCircle,
	ePolygon,
	eEmpty
};


class Canvas {
public:
	void OnMouseButtonClick(){
		// ...
	}
};

class Dialog{
	// ...
};

class PrimitiveDetailsDlg : public Dialog {
	// ...
};

//
class Toolbar {
public:
	Toolbar() = default;

	void OnCreatePrimitive() {
		PrimitiveDetailsDlg dlg;
		// Get primitive details (primitive type )
		// Activate creating primitive mode 
		m_activeShapeType = PrimitiveTypes::eLine;

		// Send message to main frame
	}

	void OnSetColorPalette() {
		// Set color for drawing primitives
	}

	void OnSelectPrimitives() {

	}

	// ...

private:
	PrimitiveTypes m_activeShapeType = PrimitiveTypes::eEmpty;
};

//template <typename R, typename ... Args>
//class MouseClickEvent {
//public:
//private:
//	std::function<R(Args...)> m_handler;
//};

//template <typename R, typename ... Args>
class MenuItem {
public:
	MenuItem(const std::string& name, const std::function<void()>& func) : m_name{ name }, m_command{ func }
	{}
	void ExecuteCommand() const {
		m_command();
	}
private:
	std::string m_name;
	std::function<void()> m_command;
};

class Menu {
public:
	Menu() = default;

	void AddItem(const MenuItem& menuItem) {
		// ...
	}

private:
	template <typename R, typename ... Args>
	std::vector<MenuItem> m_menuItems;
};

class Wnd {};
class WorkspaceWnd : public Wnd {
public:
	void OnMouseClick() {
		//...
	}
};

class EditorFrame {
public:
	EditorFrame() {
		m_menuBar.AddItem("Create New", OnCreateNewDocument);
		m_menuBar.AddItem("Import Document", OnImportDocument);
		m_menuBar.AddItem("Export Document", OnExportDocument);
	}
	void OnCreateNewDocument() {

	}

	void OnImportDocument() {

	}

	void OnExportDocument() {

	}
private:

	Menu m_menuBar;
	Toolbar* m_toolbar;
	Canvas* m_canvas;
};
// TODO: add next classes:
// - class MenuItem{};
// - class Menu {};