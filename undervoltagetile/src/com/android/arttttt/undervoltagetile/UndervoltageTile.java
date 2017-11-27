/*
 * Copyright (C) 2017 arttttt
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.android.arttttt.undervoltagetile;

import android.service.quicksettings.Tile;
import android.service.quicksettings.TileService;
import android.os.SystemProperties;

public class UndervoltageTile extends TileService {

    private final String TAG = "UndervoltageTile";
    private final String PROPERTY = "sys.perf.undervoltage";
    private boolean mEnabled;

    @Override
    public void onStartListening() {
        super.onStartListening();
	mEnabled = SystemProperties.getBoolean(PROPERTY, false);
	updateTile();
    }

    @Override
    public void onClick() {
        super.onClick();
	mEnabled = mEnabled ? false : true;
	SystemProperties.set(PROPERTY, String.valueOf(mEnabled));
	updateTile();
    }

    private void updateTile() {
	if(mEnabled)
	    getQsTile().setState(Tile.STATE_ACTIVE);
	else
	    getQsTile().setState(Tile.STATE_INACTIVE);
	getQsTile().updateTile();
    }
}
