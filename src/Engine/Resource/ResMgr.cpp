#include "precomp.h"
#include "ResMgr.h"

using namespace Engine;

ResMgr::ResMgr(const CL_String &base_path)
{
	init(base_path);
}

ResMgr::~ResMgr()
{
}

void ResMgr::init(const CL_String &base_path)
{
	vfs = CL_VirtualFileSystem(base_path, false);
	if(vfs.is_null())
		throw CL_Exception("Failed to load virtual file system!");

	vdir = vfs.get_root_directory();
}

CL_String ResMgr::getRootPath()
{
	return vfs.get_provider()->get_path();
}

std::vector<CL_String> ResMgr::getFilesInDir(const CL_String &dir)
{
	std::vector<CL_String> files;
	CL_VirtualDirectory vdirWithFiles = vdir.open_directory(dir);
	CL_VirtualDirectoryListing vdir_list = vdirWithFiles.get_directory_listing();
	while(vdir_list.next())
	{
		if(vdir_list.is_directory())
			continue;
		if(!vdir_list.is_readable())
			continue;

		files.push_back(vdir_list.get_filename());
	}
	return files;
}
