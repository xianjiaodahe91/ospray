/********************************************************************* *\
 * INTEL CORPORATION PROPRIETARY INFORMATION                            
 * This software is supplied under the terms of a license agreement or  
 * nondisclosure agreement with Intel Corporation and may not be copied 
 * or disclosed except in accordance with the terms of that agreement.  
 * Copyright (C) 2014 Intel Corporation. All Rights Reserved.           
 ********************************************************************* */

#include "mpicommon.h"

namespace ospray {
  namespace mpi {
    
    void init(int *ac, const char **av)
    {
      int initialized = false;
      MPI_Initialized(&initialized);
      if (!initialized) 
        MPI_Init(ac,(char ***)&av);
      world.comm = MPI_COMM_WORLD;
      MPI_Comm_rank(MPI_COMM_WORLD,&world.rank);
      MPI_Comm_size(MPI_COMM_WORLD,&world.size);
    }
  }

}
