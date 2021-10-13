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

	void OnCreatePrimitive(PrimitiveTypes primitiveType) {
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

template <typename R, typename ... Args>
class MenuItem {
public:
private:
	std::string m_name;
	std::function<R(Args...)> m_handler;
};

class Menu {
public:
	Menu() = default;

	template <typename R, typename ... Args>
	void AddItem(const MenuItem<R, Args...>& menuItem) {
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
		m_menuBar.AddItem<void, void>();
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