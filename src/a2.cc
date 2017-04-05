#include <PCU.h>
#include <pumi.h>
#include <iostream>
#include <list>
#include <vector>

pMeshEnt getStart(pMesh mesh)
{ //get the start vertex for reorder.
  //get the vertex that has minimum coordinates
  pMeshEnt v;
  pMeshEnt start = pumi_mesh_findEnt(mesh,
    0, 0);
  pMeshIter i = mesh->begin(0);
  while ((v = mesh->iterate(i))){
    apf::Vector3 coord;
    apf::Vector3 coord_new;
    mesh->getPoint(start, 0, coord);
    mesh->getPoint(v, 0, coord_new);
    if (coord_new[0] <= coord[0]
      && coord_new[1] <= coord[1]
      && coord_new[2] <= coord[2])
      start = v;
  }
  return start;
}


int main(int argc, char** argv)
{
  if (argc != 3) {
    printf("usage: %s reorder_?.dmg reorder_?.smb\n", argv[0]);
    return 0;
  }
  MPI_Init(&argc,&argv);
  pumi_start();
  pGeom geom = pumi_geom_load(argv[1], "mesh");
  pMesh mesh = pumi_mesh_load(geom, argv[2], 1);

  /////////////////////////////////////////
  ////Firstly get the number of nodes//////
  //////Only for linear and quadratic//////
  /////////////////////////////////////////

  //load vertices and faces first
  int labelnode = pumi_mesh_getNumEnt(mesh, 0) + 1;
  int labelface = pumi_mesh_getNumEnt(mesh, 2) + 1;
  /*SEE whether the mesh is linear or quadratic*/
  pumi_mesh_setShape(mesh, pumi_shape_getLagrange(2));
  //This is to set lagrangian manually
  pShape s = pumi_mesh_getShape(mesh);
  if (pumi_shape_getNumNode(s, PUMI_EDGE) == 1)
  {
    printf("This mesh is in second order.\n");
    labelnode = labelnode + pumi_mesh_getNumEnt(mesh, 1);
    pMeshEnt element_query;
    pMeshIter ite = mesh->begin(2);//iterate over mesh
    //to find face nodes
    while ((element_query = mesh->iterate(ite))){
      if (pumi_ment_getTopo(
        element_query) == PUMI_QUAD)
        labelnode++;
    }
  }else printf("This mesh is linear.\n");
  printf("This mesh has %d nodes.\n", labelnode-1);

  /////////////////////////////////////////
  /////////////Start reordering//////////////
  /////////////////////////////////////////
  //create numbering for nodes and elements
  pNumbering reo_node = pumi_numbering_createOwnedNode(
    mesh, "Reorder_nodes", s);
  pNumbering reo_elem = pumi_numbering_createOwned(
    mesh, "Reorder_elements", 2);
  const int labeled = 1;//if labeled then tag 1
  const int queued = 0;//if queued then tag 0
  const int labeledFace = 1;//if face labeled then tag 1
  pMeshTag IsLabeled = pumi_mesh_createIntTag(
    mesh, "Labeled node", labelnode);
  pMeshTag Isqueued = pumi_mesh_createIntTag(
    mesh, "Queued node", labelnode);
  pMeshTag FaceLabeled = pumi_mesh_createIntTag(
    mesh, "Labeled face", labelface);
  std::list<pMeshEnt> nodeQueue;
  std::list<pMeshEnt> otherVtxQueue;
  pMeshEnt e = getStart(mesh);
  nodeQueue.push_back(e);
  pumi_ment_setIntTag(e, Isqueued, &queued);
  //when enqueue a mesh entity tag it as queued.
  FILE *node_numbering = fopen("./number/Numbering.txt", "w");
  fprintf(node_numbering, "Node\t X\t Y\t Z\n");
  int vertCount = 0;
  int edgeCount = 0;
  int elemCount = 0;//Counters for nodes on verts, edges and elements
  while (nodeQueue.size() > 0){//process entities until the queue is empty
    e = nodeQueue.front();
    pumi_ment_deleteTag(e, Isqueued);
    nodeQueue.pop_front();
    apf::Vector3 node;
    mesh->getPoint(e, 0, node);
    if(pumi_ment_hasTag(e, IsLabeled) == false){
      //if node not labeled then label it//
      labelnode = labelnode - 1;
      pumi_ment_setIntTag(e, IsLabeled, &labeled);
      fprintf(node_numbering, 
      "%d\t %5.2f\t %5.2f\t %5.2f\n", labelnode, node[0],
      node[1], node[2]);
      if(pumi_ment_getDim(e) == 0){
        pumi_ment_setNumber(e, reo_node, 0, 0, labelnode);
        vertCount++;
        printf("Labelling node %d on %d vertex\n", labelnode,
          vertCount);
      }
      else if(pumi_ment_getDim(e) == 1){
        pumi_ment_setNumber(e, reo_node, 0, 0, labelnode);
        edgeCount++;
        printf("Labelling node %d on %d edge\n", labelnode,
          edgeCount);
      }
      else if(pumi_ment_getDim(e) == 2){
        pumi_ment_setNumber(e, reo_node, 0, 0, labelnode);
        elemCount++;
        printf("Labelling node %d on %d element\n", labelnode,
          elemCount);
      }
    }
    /////////////////////////////////////////
    ////Find unnuumbered nodes on adjacent mesh ents
    ////////////////////////////////////////
    if(pumi_ment_getDim(e) == 0){
      std::vector<pMeshEnt> adj_edges;
      pMeshEnt vertex = e;
      pumi_ment_getAdj(vertex, 1, adj_edges);
      for (unsigned int i = 0; i < adj_edges.size(); ++i)
      {
        pMeshEnt edge = adj_edges[i];
        std::vector<pMeshEnt> adj_faces;
        pumi_ment_getAdj(edge, 2, adj_faces);
        for (unsigned int j = 0; j < adj_faces.size(); ++j)
        {
          pMeshEnt face = adj_faces[j];
          if (pumi_ment_hasTag(face, FaceLabeled) == false)
          //if face not labeled
          {
            //label the face
            labelface = labelface - 1;
            printf("Labelling face number %d\n", labelface);
            pumi_ment_setIntTag(face, FaceLabeled, &labeledFace);
            pumi_ment_setNumber(face, reo_elem, 0, 0, labelface);
            int topo = pumi_ment_getTopo(face);
            //if face has node on it then enqueue the face
            if (pumi_shape_hasNode(s, topo) && pumi_ment_hasTag(
              face, Isqueued) == false){
              nodeQueue.push_back(face);
              pumi_ment_setIntTag(face, Isqueued, &queued);
              printf("Enqueueing a face..\n");
            }
          }
        }//finish the loop over adj faces
        pMeshEnt OtherVtx = pumi_medge_getOtherVtx(edge, vertex);
        if (pumi_shape_hasNode(s, PUMI_EDGE))//if edge has a node on it
        {
          if ((pumi_ment_hasTag(OtherVtx, IsLabeled) || pumi_ment_hasTag(
            OtherVtx, Isqueued)) && 
            pumi_ment_hasTag(edge, IsLabeled) == false)
          {//if other vertex is labeled or in queue and edge node not labeled
            labelnode = labelnode - 1;
            edgeCount++;
            mesh->getPoint(edge, 0, node);
            fprintf(node_numbering, "%d\t %5.2f\t %5.2f\t %5.2f\n", 
              labelnode, node[0], node[1], node[2]);
            printf("Labelling node number %d on %d edge\n", labelnode,
              edgeCount);
            pumi_ment_setNumber(edge, reo_node, 0, 0, labelnode);
            pumi_ment_setIntTag(edge, IsLabeled, &labeled);
          }
          else if (pumi_ment_hasTag(OtherVtx, IsLabeled) == false
            && pumi_ment_hasTag(OtherVtx, Isqueued) ==  false){
            nodeQueue.push_back(edge);
            pumi_ment_setIntTag(edge, Isqueued, &queued);
            otherVtxQueue.push_back(OtherVtx);
            pumi_ment_setIntTag(OtherVtx, Isqueued, &queued);
          }
        }//end if edge has a node
        else if(pumi_ment_hasTag(OtherVtx, IsLabeled) == false
            && pumi_ment_hasTag(OtherVtx, Isqueued) ==  false){
            otherVtxQueue.push_back(OtherVtx);
            pumi_ment_setIntTag(OtherVtx, Isqueued, &queued);
        }
      }//finish the loop over adj edges
      nodeQueue.insert(nodeQueue.end(), otherVtxQueue.begin(), 
        otherVtxQueue.end());
      otherVtxQueue.clear();
    }
  }//finish the biggest loop
  fclose(node_numbering);
  pumi_mesh_write(mesh,"number","vtk");
  pumi_mesh_delete(mesh);
  pumi_finalize();
  MPI_Finalize();
}
