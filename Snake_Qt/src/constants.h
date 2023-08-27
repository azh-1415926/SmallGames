#pragma once

#include <QRect>

/* 矩形范围 */
const QRect RANGE={25,25,450,450};
/* x 轴方向线条数量 */
const qreal NX=8.0;
/* y 轴方向线条数量 */
const qreal NY=8.0;
/* x 轴方向线条间隔 */
const qreal GAPOFX=RANGE.width()/(NX+1);
/* y 轴方向线条间隔 */
const qreal GAPOFY=RANGE.height()/(NY+1);