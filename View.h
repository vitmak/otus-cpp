#pragma once

#include <string>
#include <list>
#include <functional>


enum class PrimitiveTypes {
	ePoint = 0,
	eLine,
	eCircle,
	ePolygon,
	eEmpty
};


class Dialog{
	// ...
};

class PrimitiveDetailsDlg : public Dialog {
	// ...
};

class FilePathDlg : public Dialog {
	// ...
};


class Menu {
public:
	Menu() = default;

	void AddItem(const std::string& name) {
		// ...
	}

	void OnClick(const std::string& itemName) const {
		// find command with given name
		
		// m_menuItem->ExecuteCommand()
	}

	void SetCommand(const std::string& itemName, const std::function<void()>& func) {
		// find command with given name

		// Set command for found item.
	}

private:
	class MenuItem {
	public:
		MenuItem(const std::string& name) : m_name{ name }
		{}
		void ExecuteCommand() const {
			m_command();
		}
	private:
		std::string m_name;
		std::function<void()> m_command;
	};

	std::list<std::string, MenuItem> m_menuItems;
};

class GraphicEditorApp;
class Wnd {};
class Canvas : public Wnd {
public:
	Canvas() = default;
	void OnMouseClick(int x, int y);
};

class EditorFrame {
public:
	EditorFrame() {
		m_menuBar.AddItem("Create New");
		m_menuBar.AddItem("Import Document");
		m_menuBar.AddItem("Export Document");
		m_menuBar.AddItem("Create primitive");
		m_menuBar.AddItem("Select primitive");
		m_menuBar.AddItem("Delete primitive");
	}

	const Menu& GetMenu() const {
		return m_menuBar;
	}

	Canvas& GetCanvas() const {
		return *m_canvas;
	}
	
private:
	Menu m_menuBar;
	Canvas* m_canvas;
};
