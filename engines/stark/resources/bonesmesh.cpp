/* ResidualVM - A 3D game interpreter
 *
 * ResidualVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the AUTHORS
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "engines/stark/actor.h"
#include "engines/stark/resources/bonesmesh.h"
#include "engines/stark/services/archiveloader.h"
#include "engines/stark/services/services.h"
#include "engines/stark/formats/xrc.h"

namespace Stark {
namespace Resources {

BonesMesh::~BonesMesh() {
	delete _actor;
}

BonesMesh::BonesMesh(Object *parent, byte subType, uint16 index, const Common::String &name) :
				Object(parent, subType, index, name),
				_actor(nullptr) {
	_type = TYPE;
}

void BonesMesh::readData(Formats::XRCReadStream *stream) {
	_filename = stream->readString();
	_archiveName = stream->getArchiveName();
}

void BonesMesh::onPostRead() {
	// Get the archive loader service
	ArchiveLoader *archiveLoader = StarkServices::instance().archiveLoader;

	ArchiveReadStream *stream = archiveLoader->getFile(_filename, _archiveName);

	_actor = new Actor();
	_actor->readFromStream(stream);

	delete stream;
}

Actor *BonesMesh::getActor() {
	return _actor;
}

void BonesMesh::printData() {
	debug("filename: %s", _filename.c_str());
}

} // End of namespace Resources
} // End of namespace Stark
