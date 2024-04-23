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

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow( QWidget * parent ) :
	QMainWindow( parent ),
	m_ui( this->setupUi() ),
	m_table( *m_ui->tableWidget )
{
	this->setFixedSize( this->size() ) ;

	QIcon icon( ":/cpufrequencymonitor" ) ;

	m_tray.setIcon( icon ) ;

	this->setWindowIcon( icon ) ;

	m_timer.setInterval( 1000 ) ;

	m_ui->label->setText( m_cpus.name() ) ;

	this->prepareUi() ;

	connect( &m_timer,&QTimer::timeout,[ & ](){

		for( int s = 0 ; s < m_cpus.size() ; s++ ){

			this->updateUi( 0,s,m_cpus[ s ].update() ) ;
		}
	} ) ;

	connect( m_menu.addAction( "Quit" ),&QAction::triggered,[](){

		QCoreApplication::quit() ;
	} ) ;

	connect( m_ui->pbStart,&QPushButton::clicked,[ & ](){

		this->startTimer() ;
	} ) ;

	connect( m_ui->pbHide,&QPushButton::clicked,[ & ](){

		this->hide() ;
		this->stopTimer() ;
	} ) ;

	connect( m_ui->pbStop,&QPushButton::clicked,[ & ](){

		this->stopTimer() ;
	} ) ;

	connect( m_ui->pbQuit,&QPushButton::clicked,[ & ](){

		QCoreApplication::quit() ;
	} ) ;

	connect( &m_tray,&QSystemTrayIcon::activated,[ & ]( QSystemTrayIcon::ActivationReason ){

		if( this->isVisible() ){

			this->hide() ;

			this->stopTimer() ;
		}else{
			this->show() ;
			this->startTimer() ;
		}
	} ) ;

	m_ui->pbStart->setEnabled( false ) ;

	this->startTimer() ;

	m_ui->pbQuit->setFocus() ;

	m_tray.setContextMenu( &m_menu ) ;
	m_tray.show() ;
}

MainWindow::~MainWindow()
{
	delete m_ui ;
}

void MainWindow::stopTimer()
{
	m_timer.stop() ;

	m_ui->pbStart->setEnabled( true ) ;
	m_ui->pbStop->setEnabled( false ) ;
}

void MainWindow::startTimer()
{
	m_timer.start() ;

	m_ui->pbStop->setEnabled( true ) ;
	m_ui->pbStart->setEnabled( false ) ;
}

void MainWindow::closeEvent( QCloseEvent * )
{
	this->stopTimer() ;
}

void MainWindow::updateUi( int row,int column,const CPU& cpu )
{
	m_table.item( row + 0,column )->setText( cpu.maxSpeed() ) ;
	m_table.item( row + 1,column )->setText( cpu.baseSpeed() ) ;
	m_table.item( row + 2,column )->setText( cpu.currentSpeed() ) ;
	m_table.item( row + 3,column )->setText( cpu.ratioToMax() ) ;
}

Ui::MainWindow * MainWindow::setupUi()
{
	auto m = new Ui::MainWindow() ;

	m->setupUi( this ) ;

	return m ;
}

QTableWidgetItem * MainWindow::addItem()
{
	auto m = new QTableWidgetItem() ;
	m->setTextAlignment( Qt::AlignHCenter | Qt::AlignVCenter ) ;
	return m ;
}

void MainWindow::prepareUi()
{
	m_table.insertRow( 0 ) ;
	m_table.insertRow( 0 ) ;
	m_table.insertRow( 0 ) ;
	m_table.insertRow( 0 ) ;

	QStringList labels ;

	for( int s = 0 ; s < m_cpus.size() ; s++ ){

		m_table.insertColumn( 0 ) ;

		labels.append( "CPU" + QString::number( s ) ) ;
	}

	m_table.setHorizontalHeaderLabels( labels ) ;

	m_table.horizontalHeader()->setStretchLastSection( true ) ;
	m_table.verticalHeader()->setStretchLastSection( true ) ;

	for( int rows = 0 ; rows < m_table.rowCount() ; rows++ ){

		for( int columns = 0 ; columns < m_table.columnCount() ; columns++ ){

			m_table.setItem( rows,columns,this->addItem() ) ;
		}
	}
}
