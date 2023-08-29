#pragma once

#include <QRect>

/* 矩形范围 */
const QRect RANGE={0,0,400,400};
/* x 轴方向线条数量 */
const qreal NX=14.0;
/* y 轴方向线条数量 */
const qreal NY=14.0;
/* x 轴方向线条间隔 */
const qreal GAPOFX=RANGE.width()/(NX+1);
/* y 轴方向线条间隔 */
const qreal GAPOFY=RANGE.height()/(NY+1);