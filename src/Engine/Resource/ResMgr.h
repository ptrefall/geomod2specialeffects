#pragma once

namespace Engine
{
class ResMgr
{
public:
	ResMgr(const CL_String &base_path);
	~ResMgr();

	CL_String getRootPath();
	std::vector<CL_String> getFilesInDir(const CL_String &dir);

	CL_VirtualDirectory &getDir() { return vdir; }

private:
	void init(const CL_String &base_path);

	CL_VirtualFileSystem vfs;
	CL_VirtualDirectory vdir;
};

}
