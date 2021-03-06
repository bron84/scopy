/*
 * Copyright 2016 Analog Devices, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file LICENSE.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include "customScale.hpp"

#include <qwt_scale_engine.h>

using namespace adiscope;

CustomScale::CustomScale(QWidget *parent) :
	QwtThermo(parent)
{
	QVector<QwtScaleDiv> divs;

	divs.push_back(scaleEngine()->divideScale(-0.1, +0.1, 5, 5));
	divs.push_back(scaleEngine()->divideScale(-1.0, +1.0, 5, 5));
	divs.push_back(scaleEngine()->divideScale(-5.0, +5.0, 10, 2));
	divs.push_back(scaleEngine()->divideScale(-25.0, +25.0, 10, 5));

	scaler = new AutoScaler(this, divs);

	connect(scaler, SIGNAL(updateScale(const QwtScaleDiv)),
			this, SLOT(updateScale(const QwtScaleDiv)));
}

CustomScale::~CustomScale()
{
	delete scaler;
}

void CustomScale::updateScale(const QwtScaleDiv div)
{
	setScale(div);
}

void CustomScale::start()
{
	scaler->startTimer();
}

void CustomScale::stop()
{
	scaler->stopTimer();
}

void CustomScale::setValue(double value)
{
	scaler->setValue(value);
	QwtThermo::setValue(value);
}
