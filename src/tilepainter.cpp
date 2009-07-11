/*
 * Tiled Map Editor (Qt)
 * Copyright 2009 Tiled (Qt) developers (see AUTHORS file)
 *
 * This file is part of Tiled (Qt).
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307, USA.
 */

#include "tilepainter.h"

#include "mapdocument.h"
#include "tilelayer.h"

using namespace Tiled;
using namespace Tiled::Internal;

static inline bool outOfBounds(int x, int y, TileLayer *tileLayer)
{
    return (x < 0 ||
            y < 0 ||
            x >= tileLayer->width() ||
            y >= tileLayer->height());
}

TilePainter::TilePainter(MapDocument *mapDocument, TileLayer *tileLayer)
    : mMapDocument(mapDocument)
    , mTileLayer(tileLayer)
{
}

Tile *TilePainter::tileAt(int x, int y)
{
    const int layerX = x - mTileLayer->x();
    const int layerY = y - mTileLayer->y();

    if (outOfBounds(layerX, layerY, mTileLayer))
        return 0;

    return mTileLayer->tileAt(layerX, layerY);
}

void TilePainter::setTile(int x, int y, Tile *tile)
{
    const int layerX = x - mTileLayer->x();
    const int layerY = y - mTileLayer->y();

    if (outOfBounds(layerX, layerY, mTileLayer))
        return;

    mTileLayer->setTile(layerX, layerY, tile);
    mMapDocument->emitRegionChanged(QRegion(x, y, 1, 1));
}