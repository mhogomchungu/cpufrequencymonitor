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

#include <array>
#include <memory>

#include <QString>
#include <QByteArray>
#include <QFile>

class CPU
{
public:
	CPU( const QString& e ) ;
	CPU& update() ;
	QString currentSpeed() const ;
	QString ratioToBase() const ;
	QString ratioToMax() const ;
	QString changeDiff() const ;
	QString cpuName() const ;
	const QString& baseSpeed() const ;
	const QString& maxSpeed() const ;
private:
	std::unique_ptr< QFile > file( const QString& e ) ;
	double baseSpeed( const QString& e ) ;
	double maxSpeed( const QString& e ) ;
	std::unique_ptr< QFile > m_file ;
	double m_currentSpeed = 0 ;
	double m_oldSpeed = 0 ;
	double m_baseSpeed ;
	double m_maxSpeed ;
	QString m_baseSpeedString ;
	QString m_maxSpeedString ;
} ;

class CPUs
{
public:
	CPUs() ;
	int size() const ;
	CPU& operator[]( int ) ;
	QString name() const ;
private:
	std::vector< CPU > m_cpu ;
} ;
