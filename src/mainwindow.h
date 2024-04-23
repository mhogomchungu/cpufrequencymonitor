/*
 *
 *  Copyright (c) 2024
 *  name : Francis Banyikwa
 *  email: mhogomchungu@gmail.com
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QTimer>
#include <QTableWidget>

#include "cpu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow( QWidget * parent = nullptr ) ;
	~MainWindow() ;
private:
	void updateUi( int row,int column,const CPU& ) ;
	Ui::MainWindow * setupUi() ;
	QTableWidgetItem * addItem() ;
	void prepareUi() ;
	void stopTimer() ;
	void startTimer() ;
	void closeEvent( QCloseEvent * ) override ;
	QTimer m_timer ;
	QMenu m_menu ;
	Ui::MainWindow * m_ui ;
	QSystemTrayIcon m_tray ;
	QTableWidget& m_table ;

	CPUs m_cpus ;
} ;

#endif // MAINWINDOW_H
