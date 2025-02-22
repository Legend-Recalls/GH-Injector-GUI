#pragma once

#include "pch.h"

#include "ui_GuiProcess.h"

#include "DebugConsole.h"
#include "framelesswindow.h"
#include "StatusBox.h"
#include "Process.h"

//don't want to include QWinExtras because of static build
//but there's a problem with icon extraction returning invalid sizes so here we are
Q_GUI_EXPORT QPixmap qt_pixmapFromWinHICON(HICON icon);

struct Process_State_Struct
{
	QString			txtFilter	= QString("");
	int				cmbArch		= 0;
	bool			cbSession	= false;
};

class TreeWidgetItem : public QTreeWidgetItem 
{
public:
	TreeWidgetItem(int type = 0);

private:
	bool operator< (const QTreeWidgetItem & rhs) const;
};

class GuiProcess : public QWidget
{
	Q_OBJECT

public:
	GuiProcess(QWidget * parent = Q_NULLPTR, FramelessWindow * FramelessParent = Q_NULLPTR);
	~GuiProcess();

private:

	Ui::frm_proc ui;
	FramelessWindow * frameless_parent;

	Process_State_Struct	*		m_ProcessState;
	Process_Struct			*		m_ProcessStruct;
	QTimer					*		m_TmrUpdateList;
	QTimer					*		m_TmrFilterFocus;
	SORT_SENSE						m_SortSense;
	ULONG							m_OwnSessionID;
	std::vector<Process_Struct *>	m_ProcList;
	bool							m_bSelectedFromList;

	QPixmap m_pxmError;
	QPixmap m_pxmGeneric;

protected:
	bool eventFilter(QObject * obj, QEvent * event) override;

signals:
	void send_to_inj(Process_State_Struct * procStateStruct, Process_Struct * procStruct);

public slots:
	void get_from_inj(Process_State_Struct * procStateStruct, Process_Struct * procStruct);

private slots:
	void refresh_gui();
	void refresh_process();
	void filter_change(int i);
	void session_change();
	void name_change(const QString &);
	void proc_select(bool ignore = false);
	void custom_sort(int);
	void double_click_process(const QModelIndex & index);
};