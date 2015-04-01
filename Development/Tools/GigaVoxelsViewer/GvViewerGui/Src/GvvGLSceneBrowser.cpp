/*
 * GigaVoxels is a ray-guided streaming library used for efficient
 * 3D real-time rendering of highly detailed volumetric scenes.
 *
 * Copyright (C) 2011-2012 INRIA <http://www.inria.fr/>
 *
 * Authors : GigaVoxels Team
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/** 
 * @version 1.0
 */

#include "GvvGLSceneBrowser.h"

/******************************************************************************
 ******************************* INCLUDE SECTION ******************************
 ******************************************************************************/

// GvViewer
#include "GvvBrowserItem.h"
#include "GvvBrowsable.h"
#include "GvvContextMenu.h"
#include "GvvGLSceneInterface.h"

// Qt
#include <QContextMenuEvent>
#include <QTreeWidget>

// System
#include <cassert>

/******************************************************************************
 ****************************** NAMESPACE SECTION *****************************
 ******************************************************************************/

// GvViewer
using namespace GvViewerCore;
using namespace GvViewerGui;

/******************************************************************************
 ************************* DEFINE AND CONSTANT SECTION ************************
 ******************************************************************************/

/******************************************************************************
 ***************************** TYPE DEFINITION ********************************
 ******************************************************************************/

/******************************************************************************
 ***************************** METHOD DEFINITION ******************************
 ******************************************************************************/

/******************************************************************************
 * Default constructor.
 ******************************************************************************/
GvvGLSceneBrowser::GvvGLSceneBrowser( QWidget* pParent ) 
:	GvvBrowser( pParent )
,	GvvGLSceneManagerListener()
{
}

/******************************************************************************
 * Destructor.
 ******************************************************************************/
GvvGLSceneBrowser::~GvvGLSceneBrowser()
{
}

/******************************************************************************
 * Add a pipeline.
 *
 * @param the pipeline to add
 ******************************************************************************/
void GvvGLSceneBrowser::onGLSceneAdded( GvvGLSceneInterface* pScene )
{
	assert( pScene != NULL);
	if ( pScene != NULL )
	{
		GvvBrowserItem* sceneItem = createItem( pScene );
		addTopLevelItem( sceneItem );

		// Expand item
		expandItem( sceneItem );
	}
}

/******************************************************************************
 * Add a pipeline.
 *
 * @param the pipeline to add
 ******************************************************************************/
void GvvGLSceneBrowser::onGLSceneRemoved( GvvGLSceneInterface* pScene )
{
	// Finds the item assigned to the given browsable
	GvvBrowserItem* item = find( pScene );
	if ( item != NULL )
	{
		int index = indexOfTopLevelItem( item );
		takeTopLevelItem( index );
	}
}
