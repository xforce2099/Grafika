#pragma once

#include "../AlgebraicHyperbolic/AlgebraicHyperbolic.h"
#include "../Core/ShaderPrograms.h"
#include "../Core/Materials.h"
#include <memory>


namespace cagd
{
    class AlgebraicHyperbolicCompositeSurface3
    {
    protected:
        // possible shape parameters
        GLdouble _alpha;

    public:
        class PatchAttributes
        {
        public:
            AlgebraicHyperbolicPatch*   patch;
            TriangulatedMesh3*          image;
            Material*                   material;
            ShaderProgram*              shader;


            std::vector<PatchAttributes*> neighbours;
            // 0 - west
            // 1 - north
            // 2 - east
            // 3 - south
        };
    protected:

        std::vector<PatchAttributes*>    _attributes;

    public:
        // konstruktor
        AlgebraicHyperbolicCompositeSurface3()
        {
            _attributes.reserve(256);
            _alpha = 1.0;

        }

        // masolo konsktruktor
        AlgebraicHyperbolicCompositeSurface3(const AlgebraicHyperbolicCompositeSurface3& a)
        {
            this->_attributes = a._attributes;
        }

        // destruktor
        ~AlgebraicHyperbolicCompositeSurface3()
        {

        }

        // = operator
        AlgebraicHyperbolicCompositeSurface3& operator =(AlgebraicHyperbolicCompositeSurface3& rhs)
        {
            this->_attributes = rhs._attributes;
            set_alpha(rhs.alpha());
            return (*this);
        }

        // render data
        GLboolean RenderData(GLenum render_mode) const
        {
            glColor3f(0.0f, 0.0f, 1.0f);
            for (GLuint i = 0; i < _attributes.size(); i++)
                _attributes[i]->patch->RenderData(render_mode);
            return GL_TRUE;
        }

        GLboolean RenderControlNet()
        {
            glColor3f(0.0f, 0.0f, 1.0f);
            for (GLuint i = 0; i < _attributes.size(); i++)
                _attributes[i]->patch->RenderData(GL_LINE_STRIP);
            return GL_TRUE;
        }

        // render the surface points
        GLboolean Render()
        {
            for (GLuint i = 0; i < _attributes.size(); i++)
            {
                _attributes[i]->patch->UpdateVertexBufferObjectsOfData();
                delete _attributes[i]->image;
                _attributes[i]->image = _attributes[i]->patch->GenerateImage(10, 10, GL_STATIC_DRAW);
                _attributes[i]->image->UpdateVertexBufferObjects();
                _attributes[i]->material->Apply();
                if (_attributes[i]->shader)
                    _attributes[i]->shader->Enable();
                _attributes[i]->image->Render();
                if (_attributes[i]->shader)
                    _attributes[i]->shader->Disable();

             }
            return GL_TRUE;
        }

        // render normals
        GLboolean RenderNormals()
        {
            glColor3f(1.0f, 0.0f, 0.0f);
            for (GLuint i = 0; i < _attributes.size(); i++)
            {
                _attributes[i]->patch->UpdateVertexBufferObjectsOfData();
                delete _attributes[i]->image;
                _attributes[i]->image = _attributes[i]->patch->GenerateImage(10, 10, GL_STATIC_DRAW);
                _attributes[i]->image->UpdateVertexBufferObjects();
                _attributes[i]->image->RenderNormals();

             }
            return GL_TRUE;
        }

        // render u-directional isoparametric curves
        void renderUIsoparametric()
        {
            for (GLuint i = 0; i < _attributes.size(); i++)
            {
                _attributes[i]->material->Apply();
                RowMatrix<GenericCurve3*>* lines = _attributes[i]->patch->GenerateUIsoparametricLines(10, 1, 10);

                glColor3f(1.0f, 0.0f, 0.0f);
                for (GLuint i = 0; i < lines->GetColumnCount(); i++)
                {
                    (*lines)[i]->UpdateVertexBufferObjects();
                    (*lines)[i]->RenderDerivatives(0, GL_LINE_STRIP);
                    delete (*lines)[i];
                }

                delete lines;
            }
        }

        // render v-directional isoparametric curves
        void renderVIsoparametric()
        {
            for (GLuint i = 0; i < _attributes.size(); i++)
            {
                _attributes[i]->material->Apply();
                RowMatrix<GenericCurve3*>* lines = _attributes[i]->patch->GenerateVIsoparametricLines(10, 1, 10);

                glColor3f(1.0f, 0.0f, 0.0f);
                for (GLuint i = 0; i < lines->GetColumnCount(); i++)
                {
                    (*lines)[i]->UpdateVertexBufferObjects();
                    (*lines)[i]->RenderDerivatives(0, GL_LINE_STRIP);
                    delete (*lines)[i];
                }
                delete lines;
            }
        }


        // render U directional partial derivatives
        void renderUPartialDerivatives()
        {
            for (GLuint i = 0; i < _attributes.size(); i++)
            {
                glColor3f(0.0f, 1.0f, 0.0f);
                _attributes[i]->material->Apply();
                RowMatrix<GenericCurve3*>* lines = _attributes[i]->patch->GenerateUIsoparametricLines(10, 1, 10);

                for (GLuint i = 0; i < lines->GetColumnCount(); i++)
                {
                    (*lines).operator [](i)->UpdateVertexBufferObjects();
                    (*lines).operator [](i)->RenderDerivatives(1, GL_LINES);
                    delete (*lines).operator [](i);
                }
                delete lines;
            }
        }

        // render V directional partial derivatives
        void renderVPartialDerivatives()
        {
            glColor3f(0.0f, 1.0f, 0.0f);
            for (GLuint i = 0; i < _attributes.size(); i++)
            {
                _attributes[i]->material->Apply();
                RowMatrix<GenericCurve3*>* lines = _attributes[i]->patch->GenerateVIsoparametricLines(10, 1, 10);

                for (GLuint i = 0; i < lines->GetColumnCount(); i++)
                {
                    (*lines).operator [](i)->UpdateVertexBufferObjects();
                    (*lines).operator [](i)->RenderDerivatives(1, GL_LINES);
                    delete (*lines).operator [](i);
                }
                delete lines;
            }
        }


        // insert new isolated patch
        void insertPatch(AlgebraicHyperbolicPatch* newPatch, Material* m, ShaderProgram* s)
        {
            //std::shared_ptr<PatchAttributes> p = std::make_shared<PatchAttributes>();
            PatchAttributes* p = new PatchAttributes();

            p->patch = new AlgebraicHyperbolicPatch(_alpha);

            if (_attributes.size() == 0)
                this->set_alpha(newPatch->get_alpha());

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    double x, y, z;
                    newPatch->GetData(i, j, x, y, z);
                    p->patch->SetData(i, j, x, y, z);
                }
            }


            p->patch->UpdateVertexBufferObjectsOfData();
            p->image = p->patch->GenerateImage(30, 30, GL_STATIC_DRAW);
            p->image->UpdateVertexBufferObjects();

            p->material = m;
            p->shader = s;

            for (int i = 0; i < 8; i++)
                p->neighbours.push_back(nullptr);

            _attributes.push_back(p);
        }

        // delete patch
        void deletePatch(int index)
        {
            if (_attributes.size() != 0)
            {
                //std::shared_ptr<PatchAttributes> address = _attributes[index];
                PatchAttributes* address = _attributes[index];
                for (GLuint i = 0; i < _attributes.size(); i++)
                {
                    for (GLuint j = 0; j < 8; j++)
                    {
                        if (_attributes[i]->neighbours[j] == address)
                            _attributes[i]->neighbours[j] = 0;
                    }
                }

                if (_attributes[index]->patch != nullptr)
                    delete _attributes[index]->patch;
                if (_attributes[index]->image != nullptr)
                    delete _attributes[index]->image;
                //if (_attributes[index]->material != nullptr)
                    //delete _attributes[index]->material;

                _attributes.erase(_attributes.begin()+index);
            }
        }



        // size
        int sizeOf()
        {
            return _attributes.size();
        }



        void set_alpha(double value)
        {
            this->_alpha = value;
            double u_min, u_max, v_min, v_max;
            for (GLuint i = 0; i < _attributes.size(); i++)
            {
                AlgebraicHyperbolicPatch* mypatch = _attributes[i]->patch;
                mypatch->set_alpha(value);
                mypatch->GetUInterval(u_min, u_max);
                mypatch->GetVInterval(v_min, v_max);
                mypatch->SetUInterval(u_min, _alpha);
                mypatch->SetVInterval(v_min, _alpha);
            }
        }

        // get x of index.th patch's i'th row's j't column's data point
        double x(int index, int i, int j)
        {
            if (index != -1)
            {
                double x, y, z;
                AlgebraicHyperbolicPatch* mypatch = _attributes[index]->patch;
                mypatch->GetData(i, j, x, y, z);
                return x;
            }
            else
                return 0;
        }

        // get y of index.th patch's i'th row's j't column's data point
        double y(int index, int i, int j)
        {
            if (index != -1)
            {
                double x, y, z;
                AlgebraicHyperbolicPatch* mypatch = _attributes[index]->patch;
                mypatch->GetData(i, j, x, y, z);
                return y;
            }
            else
                return 0;
        }

        // get z of index.th patch's i'th row's j't column's data point
        double z(int index, int i, int j)
        {
            if (index != -1)
            {
                double x, y, z;
                AlgebraicHyperbolicPatch* mypatch = _attributes[index]->patch;
                mypatch->GetData(i, j, x, y, z);
                return z;
            }
            else
                return 0;
        }

        // get alpha
        double alpha()
        {
            return _alpha;
        }

        // set x of index.th patch's i'th row's j't column's data point
        void x(double newValue, int index, int i, int j)
        {
            if (index != -1)
            {
                double x, y, z;
                AlgebraicHyperbolicPatch* mypatch = _attributes[index]->patch;
                mypatch->GetData(i, j, x, y, z);
                mypatch->SetData(i, j, newValue, y, z);
                testNeighbours(index, i , j, index, 0, -1);
            }
        }

        // set y of index.th patch's i'th row's j't column's data point
        void y(double newValue, int index, int i, int j)
        {
            if (index != -1)
            {
                double x, y, z;
                AlgebraicHyperbolicPatch* mypatch = _attributes[index]->patch;
                mypatch->GetData(i, j, x, y, z);
                mypatch->SetData(i, j, x, newValue, z);
                testNeighbours(index, i , j, index, 0, -1);
            }
        }

        // set z of index.th patch's i'th row's j't column's data point
        void z(double newValue, int index, int i, int j)
        {
            if (index != -1)
            {
                double x, y, z;
                AlgebraicHyperbolicPatch* mypatch = _attributes[index]->patch;
                mypatch->GetData(i, j, x, y, z);
                mypatch->SetData(i, j, x, y, newValue);
                testNeighbours(index, i , j, index, 0, -1);
            }
        }

        // set material of index.th patch
        void material(double newMaterialIndex, int index)
        {
            if (index != -1)
            {
                Material* mm;

                if (newMaterialIndex == 0)
                    mm = new Material(MatFBBrass);
                else if (newMaterialIndex == 1)
                    mm = new Material(MatFBGold);
                else if (newMaterialIndex == 2)
                    mm = new Material(MatFBSilver);
                else if (newMaterialIndex == 3)
                    mm = new Material(MatFBEmerald);
                else if (newMaterialIndex == 4)
                    mm = new Material(MatFBPearl);
                else if (newMaterialIndex == 5)
                    mm = new Material(MatFBRuby);
                else
                    mm = new Material(MatFBTurquoise);

                Material* mymaterial = _attributes[index]->material;
                delete mymaterial;
                _attributes[index]->material = mm;
            }
        }




        // test neighbours if a control point was modified
        void testNeighbours(GLint index, int i, int j, int dontReachThis, GLint depth, GLuint prevInd)
        {
            if (index != -1)
            {
                if (depth == 3)
                    return;

                if (index == dontReachThis && depth == 3)
                    return;

                PatchAttributes* modified = _attributes[index];


                double x, y, z;
                double xx, yy, zz;

                // a kontrol halo negy reszet nezzuk
                if (i < 2 && j < 2)
                {
                    // eszakra es nyugatra megyunk el
                     PatchAttributes* neighbourN = _attributes[index]->neighbours[0];
                    PatchAttributes* neighbourW = _attributes[index]->neighbours[3];


                    // eszakra
                    if (neighbourN)
                    {
                        modified->patch->GetData(0, j, x, y, z);
                        modified->patch->GetData(1, j, xx, yy, zz);

                        if (i == 0)         // ha az osszekapcsolt pont valtozott meg eszakra
                            neighbourN->patch->SetData(3, j, x, y, z);
                            neighbourN->patch->SetData(2, j, 2*x - xx, 2*y - yy, 2*z - zz);

                        // megkeressuk, hogy hanyadik index (k) a szomszed es tovabbmegyunk
                        for (GLuint k = 0; k < _attributes.size(); k++)
                        {
                            if (_attributes[k] == neighbourN)
                            {
                                if (k != prevInd)
                                {
                                    testNeighbours(k, 3, j, dontReachThis, depth+1, index);
                                    testNeighbours(k, 2, j, dontReachThis, depth+1, index);
                                }
                            }
                        }
                    }

                    // nyugatra
                    if (neighbourW)
                    {
                        modified->patch->GetData(i, 0, x, y, z);
                        modified->patch->GetData(i, 1, xx, yy, zz);

                        if (j == 0)         // ha az osszekapcsolt pont valtozott meg
                            neighbourW->patch->SetData(i, 3, x, y, z);
                        neighbourW->patch->SetData(i, 2, 2*x - xx, 2*y - yy, 2*z - zz);

                        // megkeressuk, hogy hanyadik index (k) a szomszed es tovabbmegyunk
                        for (GLuint k = 0; k < _attributes.size(); k++)
                        {
                            if (_attributes[k] == neighbourW)
                            {
                                if (k != prevInd)
                                {
                                        testNeighbours(k, i, 3, dontReachThis, depth+1, index);
                                        testNeighbours(k, i, 2, dontReachThis, depth+1, index);
                                }
                            }
                        }
                    }
                }

                else if (i < 2 && j >= 2)
                {
                    // eszakra es keletre megyunk el
                    PatchAttributes* neighbourN = _attributes[index]->neighbours[0];
                    PatchAttributes* neighbourE = _attributes[index]->neighbours[1];


                    // eszakra
                    if (neighbourN)
                    {
                        modified->patch->GetData(0, j, x, y, z);
                        modified->patch->GetData(1, j, xx, yy, zz);

                        if (i == 0)         // ha az osszekapcsolt pont valtozott meg eszakra
                            neighbourN->patch->SetData(3, j, x, y, z);
                        neighbourN->patch->SetData(2, j, 2*x - xx, 2*y - yy, 2*z - zz);

                        // megkeressuk, hogy hanyadik index (k) a szomszed es tovabbmegyunk
                        for (GLuint k = 0; k < _attributes.size(); k++)
                        {
                            if (_attributes[k] == neighbourN)
                            {
                                if (k != prevInd)
                                {
                                    testNeighbours(k, 3, j, dontReachThis, depth+1, index);
                                    testNeighbours(k, 2, j, dontReachThis, depth+1, index);
                                }
                            }
                        }
                    }


                    // keletre
                    if (neighbourE)
                    {
                        modified->patch->GetData(i, 3, x, y, z);
                        modified->patch->GetData(i, 2, xx, yy, zz);

                        if (j == 3)         // ha az osszekapcsolt pont valtozott meg
                            neighbourE->patch->SetData(i, 0, x, y, z);
                        neighbourE->patch->SetData(i, 1, 2*x - xx, 2*y - yy, 2*z - zz);

                        // megkeressuk, hogy hanyadik index (k) a szomszed es tovabbmegyunk
                        for (GLuint k = 0; k < _attributes.size(); k++)
                        {
                            if (_attributes[k] == neighbourE)
                            {
                                if (k != prevInd)
                                {
                                    testNeighbours(k, i, 0, dontReachThis, depth+1, index);
                                    testNeighbours(k, i, 1, dontReachThis, depth+1, index);
                                }
                            }
                        }
                    }


                }
                else if (i >= 2 && j < 2)
                {
                    // delre es nyugatra megyunk el

                   PatchAttributes* neighbourS = _attributes[index]->neighbours[2];
                   PatchAttributes* neighbourW = _attributes[index]->neighbours[3];

                    // delre
                    if (neighbourS)
                    {
                        modified->patch->GetData(3, j, x, y, z);
                        modified->patch->GetData(2, j, xx, yy, zz);

                        if (i == 3)         // ha az osszekapcsolt pont valtozott meg eszakra
                            neighbourS->patch->SetData(0, j, x, y, z);
                        neighbourS->patch->SetData(1, j, 2*x - xx, 2*y - yy, 2*z - zz);

                        // megkeressuk, hogy hanyadik index (k) a szomszed es tovabbmegyunk
                        for (GLuint k = 0; k < _attributes.size(); k++)
                        {
                            if (_attributes[k] == neighbourS)
                            {
                                if (k != prevInd)
                                {
                                    testNeighbours(k, 0, j, dontReachThis, depth+1, index);
                                    testNeighbours(k, 1, j, dontReachThis, depth+1, index);
                                }
                            }
                        }
                    }

                    // nyugatra
                    if (neighbourW)
                    {
                        modified->patch->GetData(i, 0, x, y, z);
                        modified->patch->GetData(i, 1, xx, yy, zz);

                        if (j == 0)         // ha az osszekapcsolt pont valtozott meg
                            neighbourW->patch->SetData(i, 3, x, y, z);
                        neighbourW->patch->SetData(i, 2, 2*x - xx, 2*y - yy, 2*z - zz);

                        // megkeressuk, hogy hanyadik index (k) a szomszed es tovabbmegyunk
                        for (GLuint k = 0; k < _attributes.size(); k++)
                        {
                            if (_attributes[k] == neighbourW)
                            {
                                if (k != prevInd)
                                {
                                    testNeighbours(k, i, 3, dontReachThis, depth+1, index);
                                    testNeighbours(k, i, 2, dontReachThis, depth+1, index);
                                }
                            }
                        }
                    }
                }
                else if (i >= 2 && j >= 2)
                {
                    // delre es keletre megyunk el
                    PatchAttributes* neighbourS = _attributes[index]->neighbours[2];
                    PatchAttributes* neighbourE = _attributes[index]->neighbours[1];

                    // delre
                    if (neighbourS)
                    {
                        modified->patch->GetData(3, j, x, y, z);
                        modified->patch->GetData(2, j, xx, yy, zz);

                        if (i == 3)         // ha az osszekapcsolt pont valtozott meg eszakra
                            neighbourS->patch->SetData(0, j, x, y, z);
                        neighbourS->patch->SetData(1, j, 2*x - xx, 2*y - yy, 2*z - zz);

                        // megkeressuk, hogy hanyadik index (k) a szomszed es tovabbmegyunk
                        for (GLuint k = 0; k < _attributes.size(); k++)
                        {
                            if (_attributes[k] == neighbourS)
                            {
                                if (k != prevInd)
                                {
                                    testNeighbours(k, 0, j, dontReachThis, depth+1, index);
                                    testNeighbours(k, 1, j, dontReachThis, depth+1, index);
                                }
                            }
                        }
                    }

                    // keletre
                    if (neighbourE)
                    {
                        modified->patch->GetData(i, 3, x, y, z);
                        modified->patch->GetData(i, 2, xx, yy, zz);

                        if (j == 3)         // ha az osszekapcsolt pont valtozott meg
                            neighbourE->patch->SetData(i, 0, x, y, z);
                        neighbourE->patch->SetData(i, 1, 2*x - xx, 2*y - yy, 2*z - zz);

                        // megkeressuk, hogy hanyadik index (k) a szomszed es tovabbmegyunk
                        for (GLuint k = 0; k < _attributes.size(); k++)
                        {
                            if (_attributes[k] == neighbourE)
                            {
                                if (k != prevInd)
                                {
                                    testNeighbours(k, i, 0, dontReachThis, depth+1, index);
                                    testNeighbours(k, i, 1, dontReachThis, depth+1, index);
                                }
                            }
                        }
                    }
                }
            }

        }





        // continue existing patch (N,S,W,E) (direction: enum)
        void continuePatch(int index, int direction)
        {
            if (index != -1)
            {
                PatchAttributes* PatchToBeContinued = _attributes[index];
                PatchAttributes* p = new PatchAttributes();

                p->patch = new AlgebraicHyperbolicPatch(_alpha);

                DCoordinate3 firstData[4];
                DCoordinate3 secondData[4];

                if (direction == 0)             // north
                {
                    int row = 0;
                    for (int j = 0; j < 4; j++)
                    {
                        PatchToBeContinued->patch->GetData(row, j, firstData[j]);
                        PatchToBeContinued->patch->GetData(row+1, j, secondData[j]);
                    }
                }
                else if (direction == 1)        // east
                {
                    int column = 3;
                    for (int i = 0; i < 4; i++)
                    {
                        PatchToBeContinued->patch->GetData(i, column, firstData[i]);
                        PatchToBeContinued->patch->GetData(i, column-1, secondData[i]);
                    }
                }
                else if (direction == 2)        // south
                {
                    int row = 3;
                    for (int j = 0; j < 4; j++)
                    {
                        PatchToBeContinued->patch->GetData(row, j, firstData[j]);
                        PatchToBeContinued->patch->GetData(row-1, j, secondData[j]);
                    }
                }
                else if (direction == 3)        // west
                {
                    int column = 0;
                    for (int i = 0; i < 4; i++)
                    {
                        PatchToBeContinued->patch->GetData(i, column, firstData[i]);
                        PatchToBeContinued->patch->GetData(i, column+1, secondData[i]);
                    }
                }


                if (direction < 4)
                {
                    for (int i = 0; i < 4; i++)
                        p->patch->SetData(i, 0, firstData[i]);

                    for (int i = 0; i < 4; i++)
                    {
                        p->patch->SetData(i, 1, firstData[i] + 1*(firstData[i] - secondData[i]));
                        p->patch->SetData(i, 2, firstData[i] + 2*(firstData[i] - secondData[i]));
                        p->patch->SetData(i, 3, firstData[i] + 3*(firstData[i] - secondData[i]));
                    }
                }
                else if (direction >= 4)
                {
                    DCoordinate3 mainCoord;
                    if (direction == 4)         // north-east
                        PatchToBeContinued->patch->GetData(0, 3, mainCoord);
                    else if (direction == 5)    // south-east
                        PatchToBeContinued->patch->GetData(3, 3, mainCoord);
                    else if (direction == 6)    // south-west
                        PatchToBeContinued->patch->GetData(3, 0, mainCoord);
                    else if (direction == 7)    // north-west
                        PatchToBeContinued->patch->GetData(0, 0, mainCoord);

                    for (int i = 0; i < 4; i++)
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            DCoordinate3 coord;
                            PatchToBeContinued->patch->GetData(j, i, coord);
                            p->patch->SetData(i, j, 2 * mainCoord - coord);
                        }
                    }
                }

                p->patch->UpdateVertexBufferObjectsOfData();
                p->image = p->patch->GenerateImage(30, 30, GL_STATIC_DRAW);
                p->image->UpdateVertexBufferObjects();

                p->material = PatchToBeContinued->material;


                p->shader = PatchToBeContinued->shader;


                for (int i = 0; i < 8; i++)
                    p->neighbours.push_back(nullptr);

                _attributes.push_back(p);


                // beallitjuk a szomszedokat (sarkakat nem allitjuk)
                if (direction < 4)
                {
                    _attributes[index]->neighbours[direction] = p;
                    if (direction == 0)
                        p->neighbours[2] = _attributes[index];
                    else if (direction == 1)
                        p->neighbours[3] = _attributes[index];
                    else if (direction == 2)
                        p->neighbours[0] = _attributes[index];
                    else if (direction == 3)
                        p->neighbours[1] = _attributes[index];
                }
            }
        }


        // join patches
        void joinPatches(int index, int index2, int direction, int direction2, ShaderProgram* s)
        {
            if (index != -1 && index2 != -1)
            {
                PatchAttributes* joined = new PatchAttributes();

                joined->patch = new AlgebraicHyperbolicPatch(_alpha);

                joined->patch->UpdateVertexBufferObjectsOfData();

                joined->image = joined->patch->GenerateImage(30, 30, GL_STATIC_DRAW);
                joined->image->UpdateVertexBufferObjects();

                joined->material = new Material(MatFBBrass);
                joined->shader = s;


                for (int i = 0; i < 8; i++)
                    joined->neighbours.push_back(nullptr);


                AlgebraicHyperbolicPatch* firstPatch = _attributes[index]->patch;

                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        double x, y, z;
                        firstPatch->GetData(i, j, x, y, z);
                        joined->patch->SetData(i, j, x, y, z);
                    }
                }



                int firstRow = 0;
                int firstColumn = 0;

                // az elso patch north
                if (direction == 0)
                {
                    int row = 0;
                    for (int j = 0; j < 4; j++)
                    {
                        joined->patch->SetData(3-firstRow, j, x(index, row, j),
                                                              y(index, row, j),
                                                              z(index, row, j));
                    }

                    row = 1;
                    for (int j = 0; j < 4; j++)
                    {
                        joined->patch->SetData(3-firstRow-1, j, 2*x(index, row-1, j) - x(index, row, j),
                                                                2*y(index, row-1, j) - y(index, row, j),
                                                                2*z(index, row-1, j) - z(index, row, j));
                    }
                }
                // az elso patch east
                else if (direction == 1)
                {
                    int column = 3;
                    for (int i = 0; i < 4; i++)
                    {
                        joined->patch->SetData(i, firstColumn, x(index, i, column),
                                                               y(index, i, column),
                                                               z(index, i, column));
                    }

                    column = 2;
                    for (int i = 0; i < 4; i++)
                    {
                        joined->patch->SetData(i, firstColumn+1, 2*x(index, i, column+1) - x(index, i, column),
                                                                 2*y(index, i, column+1) - y(index, i, column),
                                                                 2*z(index, i, column+1) - z(index, i, column));
                    }
                }
                // az elso patch south
                else if (direction == 2)
                {
                    int row = 3;
                    for (int j = 0; j < 4; j++)
                    {
                        joined->patch->SetData(firstRow, j, x(index, row, j),
                                                            y(index, row, j),
                                                            z(index, row, j));
                    }

                    row = 2;
                    for (int j = 0; j < 4; j++)
                    {
                        joined->patch->SetData(firstRow+1, j, 2*x(index, row+1, j) - x(index, row, j),
                                                              2*y(index, row+1, j) - y(index, row, j),
                                                              2*z(index, row+1, j) - z(index, row, j));
                    }
                }
                // az elso patch west
                else if (direction == 3)
                {
                    int column = 0;
                    for (int i = 0; i < 4; i++)
                    {
                        joined->patch->SetData(i, 3+firstColumn, x(index, i, column),
                                                                 y(index, i, column),
                                                                 z(index, i, column));
                    }

                    column = 1;
                    for (int i = 0; i < 4; i++)
                    {
                        joined->patch->SetData(i, 3+firstColumn-1, 2*x(index, i, column-1) - x(index, i, column),
                                                                   2*y(index, i, column-1) - y(index, i, column),
                                                                   2*z(index, i, column-1) - z(index, i, column));
                    }
                }



                // a masodik patch a masodik felet hatarozza meg a joined-nak
                firstRow = 3;
                firstColumn = 3;

                // a patch north
                if (direction2 == 0)
                {
                    int row = 0;
                    for (int j = 0; j < 4; j++)
                    {
                        joined->patch->SetData(firstRow, j, x(index2, row, j),
                                                            y(index2, row, j),
                                                            z(index2, row, j));
                    }

                    row = 1;
                    for (int j = 0; j < 4; j++)
                    {
                        joined->patch->SetData(firstRow-1, j, 2*x(index2, row-1, j) - x(index2, row, j),
                                                              2*y(index2, row-1, j) - y(index2, row, j),
                                                              2*z(index2, row-1, j) - z(index2, row, j));
                    }
                }
                // a patch east
                else if (direction2 == 1)
                {
                    int column = 3;
                    for (int i = 0; i < 4; i++)
                    {
                        joined->patch->SetData(i, firstColumn-3, x(index2, i, column),
                                                                 y(index2, i, column),
                                                                 z(index2, i, column));
                    }

                    column = 2;
                    for (int i = 0; i < 4; i++)
                    {
                        joined->patch->SetData(i, firstColumn-3+1, 2*x(index2, i, column+1) - x(index2, i, column),
                                                                   2*y(index2, i, column+1) - y(index2, i, column),
                                                                   2*z(index2, i, column+1) - z(index2, i, column));
                    }
                }
                // a patch south
                else if (direction2 == 2)
                {
                    int row = 3;
                    for (int j = 0; j < 4; j++)
                    {
                        joined->patch->SetData(firstRow-3, j, x(index2, row, j),
                                                              y(index2, row, j),
                                                              z(index2, row, j));
                    }

                    row = 2;
                    for (int j = 0; j < 4; j++)
                    {
                        joined->patch->SetData(firstRow-3+1, j, 2*x(index2, row+1, j) - x(index2, row, j),
                                                                2*y(index2, row+1, j) - y(index2, row, j),
                                                                2*z(index2, row+1, j) - z(index2, row, j));
                    }
                }
                // a patch west
                else if (direction2 == 3)
                {
                    int column = 0;
                    for (int i = 0; i < 4; i++)
                    {
                        joined->patch->SetData(i, firstColumn, x(index2, i, column),
                                                               y(index2, i, column),
                                                               z(index2, i, column));
                    }

                    column = 1;
                    for (int i = 0; i < 4; i++)
                    {
                        joined->patch->SetData(i, firstColumn-1, 2*x(index2, i, column-1) - x(index2, i, column),
                                                                 2*y(index2, i, column-1) - y(index2, i, column),
                                                                 2*z(index2, i, column-1) - z(index2, i, column));
                    }
                }

                joined->neighbours[direction2] = _attributes[index];
                joined->neighbours[direction] = _attributes[index2];

                _attributes.push_back(joined);

                _attributes[index]->neighbours[direction] = joined;
                _attributes[index2]->neighbours[direction2] = joined;

            }

        }






        // merge patches
        void mergePatches(int index, int index2, int direction, int direction2) //int depth = 0)
        {
            if (index != -1 && index2 != -1)
            {
                DCoordinate3 fromFirstPatch[4];
                DCoordinate3 fromSecondPatch[4];


                // north
                if (direction == 0)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        fromFirstPatch[j].x() = x(index, 1, j);
                        fromFirstPatch[j].y() = y(index, 1, j);
                        fromFirstPatch[j].z() = z(index, 1, j);
                    }
                }
                // east
                else if (direction == 1)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        fromFirstPatch[i].x() = x(index, i, 2);
                        fromFirstPatch[i].y() = y(index, i, 2);
                        fromFirstPatch[i].z() = z(index, i, 2);
                    }
                }
                // south
                else if (direction == 2)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        fromFirstPatch[j].x() = x(index, 2, j);
                        fromFirstPatch[j].y() = y(index, 2, j);
                        fromFirstPatch[j].z() = z(index, 2, j);
                    }
                }
                // west
                else if (direction == 3)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        fromFirstPatch[i].x() = x(index, i, 1);
                        fromFirstPatch[i].y() = y(index, i, 1);
                        fromFirstPatch[i].z() = z(index, i, 1);
                    }
                }

                // north
                if (direction2 == 0)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        fromSecondPatch[j].x() = x(index2, 1, j);
                        fromSecondPatch[j].y() = y(index2, 1, j);
                        fromSecondPatch[j].z() = z(index2, 1, j);
                    }
                }
                // east
                else if (direction2 == 1)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        fromSecondPatch[i].x() = x(index2, i, 2);
                        fromSecondPatch[i].y() = y(index2, i, 2);
                        fromSecondPatch[i].z() = z(index2, i, 2);
                    }
                }
                // south
                else if (direction2 == 2)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        fromSecondPatch[j].x() = x(index2, 2, j);
                        fromSecondPatch[j].y() = y(index2, 2, j);
                        fromSecondPatch[j].z() = z(index2, 2, j);
                    }
                }
                // west
                else if (direction2 == 3)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        fromSecondPatch[i].x() = x(index2, i, 1);
                        fromSecondPatch[i].y() = y(index2, i, 1);
                        fromSecondPatch[i].z() = z(index2, i, 1);
                    }
                }

                // ================================================================
                // allitjuk a pontokat
                // elso
                // north
                if (direction == 0)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        x(0.5*(fromFirstPatch[j].x() + fromSecondPatch[j].x()), index, 0, j);
                        y(0.5*(fromFirstPatch[j].y() + fromSecondPatch[j].y()), index, 0, j);
                        z(0.5*(fromFirstPatch[j].z() + fromSecondPatch[j].z()), index, 0, j);
                    }
                }
                // east
                else if (direction == 1)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        x(0.5*(fromFirstPatch[i].x() + fromSecondPatch[i].x()), index, i, 3);
                        y(0.5*(fromFirstPatch[i].y() + fromSecondPatch[i].y()), index, i, 3);
                        z(0.5*(fromFirstPatch[i].z() + fromSecondPatch[i].z()), index, i, 3);
                    }
                }
                // south
                else if (direction == 2)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        x(0.5*(fromFirstPatch[j].x() + fromSecondPatch[j].x()), index, 3, j);
                        y(0.5*(fromFirstPatch[j].y() + fromSecondPatch[j].y()), index, 3, j);
                        z(0.5*(fromFirstPatch[j].z() + fromSecondPatch[j].z()), index, 3, j);
                    }
                }
                // west
                else if (direction == 3)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        x(0.5*(fromFirstPatch[i].x() + fromSecondPatch[i].x()), index, i, 0);
                        y(0.5*(fromFirstPatch[i].y() + fromSecondPatch[i].y()), index, i, 0);
                        z(0.5*(fromFirstPatch[i].z() + fromSecondPatch[i].z()), index, i, 0);
                    }
                }



                // masodik
                if (direction2 == 0)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        x(0.5*(fromFirstPatch[j].x() + fromSecondPatch[j].x()), index2, 0, j);
                        y(0.5*(fromFirstPatch[j].y() + fromSecondPatch[j].y()), index2, 0, j);
                        z(0.5*(fromFirstPatch[j].z() + fromSecondPatch[j].z()), index2, 0, j);
                    }
                }
                // east
                else if (direction2 == 1)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        x(0.5*(fromFirstPatch[i].x() + fromSecondPatch[i].x()), index2, i, 3);
                        y(0.5*(fromFirstPatch[i].y() + fromSecondPatch[i].y()), index2, i, 3);
                        z(0.5*(fromFirstPatch[i].z() + fromSecondPatch[i].z()), index2, i, 3);
                    }
                }
                // south
                else if (direction2 == 2)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        x(0.5*(fromFirstPatch[j].x() + fromSecondPatch[j].x()), index2, 3, j);
                        y(0.5*(fromFirstPatch[j].y() + fromSecondPatch[j].y()), index2, 3, j);
                        z(0.5*(fromFirstPatch[j].z() + fromSecondPatch[j].z()), index2, 3, j);
                    }
                }
                // west
                else if (direction2 == 3)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        x(0.5*(fromFirstPatch[i].x() + fromSecondPatch[i].x()), index2, i, 0);
                        y(0.5*(fromFirstPatch[i].y() + fromSecondPatch[i].y()), index2, i, 0);
                        z(0.5*(fromFirstPatch[i].z() + fromSecondPatch[i].z()), index2, i, 0);
                    }
                }

                // beallitjuk a szomszedokat
                _attributes[index]->neighbours[direction] = _attributes[index2];
                _attributes[index2]->neighbours[direction2] = _attributes[index];

            }
        }



        int whichIndexIsIthNeighbour(int index, int which)
        {
            // megkeressuk, hogy hanyadik index a szomszed
            for (GLuint k = 0; k < _attributes.size(); k++)
                if (_attributes[k] == _attributes[index]->neighbours[which])
                    return k;
            return -1;
        }

        void setNeighbour(int index, int Nindex, int which)
        {
            if (Nindex == -1)
                _attributes[index]->neighbours[which] = nullptr;
            else
                _attributes[index]->neighbours[which] = _attributes[Nindex];
        }

    };
}
