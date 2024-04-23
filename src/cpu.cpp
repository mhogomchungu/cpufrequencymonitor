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

#include "cpu.h"

CPU::CPU( const QString& e ) :
	m_file( this->file( e ) ),
	m_baseSpeed( this->baseSpeed( e ) ),
	m_maxSpeed( this->maxSpeed( e ) ),
	m_baseSpeedString( QString::number( static_cast< int >( m_baseSpeed ) / 1000 ) + " MHz" ),
	m_maxSpeedString( QString::number( static_cast< int >( m_maxSpeed ) / 1000 ) + " MHz" )
{
	m_file->open( QIODevice::ReadOnly ) ;
}

CPU& CPU::update()
{
	m_oldSpeed = m_currentSpeed ;
	m_currentSpeed = m_file->readAll().toDouble() ;
	m_file->reset() ;
	return *this ;
}

QString CPU::currentSpeed() const
{
	return QString::number( static_cast< int >( m_currentSpeed ) / 1000 ) + " MHz" ;
}

QString CPU::ratioToBase() const
{
	return QString::number( m_currentSpeed / m_baseSpeed,'f',2 ) ;
}

QString CPU::ratioToMax() const
{
	return QString::number( m_currentSpeed * 100 / m_maxSpeed,'f',0 ) + "%" ;
}

QString CPU::changeDiff() const
{
	if( m_oldSpeed ){

		auto m = ( m_currentSpeed - m_oldSpeed ) * 100 / m_oldSpeed ;

		return QString::number( m,'f',2 ) + "%" ;
	}else{
		return QString( "0%" ) ;
	}
}

const QString& CPU::baseSpeed() const
{
	return m_baseSpeedString ;
}

const QString& CPU::maxSpeed() const
{
	return m_maxSpeedString ;
}

std::unique_ptr< QFile > CPU::file( const QString& e )
{
	auto m = QString( "/sys/devices/system/cpu/%1/cpufreq/scaling_cur_freq" ).arg( e ) ;

	return std::make_unique< QFile >( m ) ;
}

double CPU::baseSpeed( const QString& e )
{
	QFile f( QString( "/sys/devices/system/cpu/%1/cpufreq/scaling_min_freq" ).arg( e ) ) ;

	f.open( QIODevice::ReadOnly ) ;

	return f.readAll().toDouble() ;
}

double CPU::maxSpeed( const QString& e )
{
	QFile f( QString( "/sys/devices/system/cpu/%1/cpufreq/scaling_max_freq" ).arg( e ) ) ;

	f.open( QIODevice::ReadOnly ) ;

	return f.readAll().toDouble() ;
}

CPUs::CPUs()
{
	QString m = "/sys/devices/system/cpu/cpu%1/cpufreq/scaling_min_freq" ;

	for( int s = 0 ; ; s++ ){

		auto number = QString::number( s ) ;

		if( QFile::exists( m.arg( number ) ) ){

			m_cpu.emplace_back( "cpu" + number ) ;
		}else{
			break ;
		}
	}
}

int CPUs::size() const
{
	return static_cast< int >( m_cpu.size() ) ;
}

CPU& CPUs::operator[]( int s )
{
	return m_cpu[ static_cast< size_t >( s ) ] ;
}

QString CPUs::name() const
{
	QFile f( "/proc/cpuinfo" ) ;

	f.open( QIODevice::ReadOnly ) ;

	auto m = f.readAll().split( '\n' ) ;

	for( int s = 0 ; s < m.size() ; s++ ){

		if( m[ s ].startsWith( "model name" ) ){

			auto e = m[ s ].split( ':' ) ;

			if( e.size() ){

				return e[ 1 ].trimmed() ;
			}
		}
	}

	return {} ;
}
