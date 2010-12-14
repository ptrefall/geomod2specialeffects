#include "precomp.h"
#include "WorkProductionDoneSync.h"

using namespace Engine;

WorkProductionDoneSync::WorkProductionDoneSync(unsigned int num_jobs)
: num_jobs(num_jobs), handled(false)
{
}

WorkProductionDoneSync::~WorkProductionDoneSync()
{
}
