#pragma once

#include "AlgebraicHyperbolicArc3.h"
#include "Core/Colors4.h"
#include "Core/Constants.h"
#include <memory>

namespace cagd
{
    class AlgebraicHyperbolicCompositeCurve3
    {
    protected:
        // possible shape parameters
        GLdouble _alpha;

    public:
        class ArcAttributes
        {
        public:
            AlgebraicHyperbolicArc3* arc;
            GenericCurve3* image;
            Color4* color;

            std::shared_ptr<ArcAttributes> next;                    // jobbroli szomszed
            std::shared_ptr<ArcAttributes> previous;                // baloldali szomszed
        };
    protected:
        std::vector<std::shared_ptr<ArcAttributes>> _attributes;
    public:
        // konstruktor
        AlgebraicHyperbolicCompositeCurve3()
        {
            _alpha = 1.0;
            // ha szeretnenk inicializalni egy kezdet, (0,0,0) pontban levo ivet:
            /*
           ArcAttributes a;
           int _alpha = 1.0;
           a.arc = new AlgebraicHyperbolicArc3(_alpha);

           GLdouble step2 = TWO_PI/7;
           GLdouble t2 = 0;

           for (int i = 0; i < 4; i++, t2 += step2)
           {
               DCoordinate3 &cp = (*a.arc)[i];
               //cp.x() = cos(t2);
               //cp.y() = sin(t2);
               cp.x() = 0;
               cp.y() = 0;
               cp.z() = 0;
           }

           a.arc->UpdateVertexBufferObjectsOfData();

           a.image = a.arc->GenerateImage(30, 30, GL_STATIC_DRAW);
           a.image->UpdateVertexBufferObjects();

           a.color = new Color4();
           a.color->r() = 1.0;
           a.color->g() = 0.0;
           a.color->b() = 0.0;

           _attributes.push_back(a);
            */

        }

        // copy konstruktor
        AlgebraicHyperbolicCompositeCurve3(AlgebraicHyperbolicCompositeCurve3& a)
        {
            this->_attributes = a._attributes;
            this->set_alpha(a.alpha());
        }

        // destruktor
        ~AlgebraicHyperbolicCompositeCurve3()
        {

        }

        // =
        AlgebraicHyperbolicCompositeCurve3& operator =(AlgebraicHyperbolicCompositeCurve3& rhs)
        {
            this->_attributes = rhs._attributes;
            this->set_alpha(rhs.alpha());
            return (*this);
        }



        // render data
        GLboolean RenderData(GLenum render_mode) const
        {
            glColor3f(0.0f, 0.0f, 1.0f);
            for (GLuint i = 0; i < _attributes.size(); i++)
                _attributes[i]->arc->RenderData(render_mode);
            return GL_TRUE;
        }


        // render derivatives
        GLboolean RenderDerivatives(GLuint order, GLenum render_mode)
        {

            for (GLuint i = 0; i < _attributes.size(); i++)
            {
                _attributes[i]->arc->UpdateVertexBufferObjectsOfData();
                delete _attributes[i]->image;
                _attributes[i]->image = _attributes[i]->arc->GenerateImage(30, 30, GL_STATIC_DRAW);
                _attributes[i]->image->UpdateVertexBufferObjects();


                if (_attributes[i]->image)
                {
                    if (order == 0)
                    {
                        float red = _attributes[i]->color->r();
                        float green = _attributes[i]->color->g();
                        float blue = _attributes[i]->color->b();
                        glColor3f(red, green, blue);
                    }
                    else if (order == 1)
                    {
                        glColor3f(0.0f, 0.5f, 0.0f);
                    }
                    else if (order == 2)
                    {
                        glColor3f(0.0f, 0.8f, 1.0f);
                    }
                    _attributes[i]->image->RenderDerivatives(order, render_mode);
                }
             }
            return GL_TRUE;
        }


        // size
        int sizeOf()
        {
            return _attributes.size();
        }

        // get x of index.th arc's i'th data point
        double x(int index, int i)
        {
            if (index != -1)
            {
                AlgebraicHyperbolicArc3* myarc = _attributes[index]->arc;
                return myarc->operator [](i).x();
            }
            else
                return 0;
        }

        // get y of index.th arc's i'th data point
        double y(int index, int i)
        {
            if (index != -1)
            {
                AlgebraicHyperbolicArc3* myarc = _attributes[index]->arc;
                return myarc->operator [](i).y();
            }
            else
                return 0;
        }

        // get z of index.th arc's i'th data point
        double z(int index, int i)
        {
            if (index != -1)
            {
                AlgebraicHyperbolicArc3* myarc = _attributes[index]->arc;
                return myarc->operator [](i).z();
            }
            else
                return 0;
        }


        // get alpha
        double alpha()
        {
            return _alpha;
        }



        // set x of index.th arc's i'th data point
        void x(double newValue, int index, int i)
        {
            if (index != -1)
            {
                AlgebraicHyperbolicArc3* myarc = _attributes[index]->arc;
                myarc->operator [](i).x() = newValue;
                testNeighbours(index, i);
            }
        }


        // set y of index.th arc's i'th data point
        void y(double newValue, int index, int i)
        {
            if (index != -1)
            {
                AlgebraicHyperbolicArc3* myarc = _attributes[index]->arc;
                myarc->operator [](i).y() = newValue;
                testNeighbours(index, i);
            }
        }


        // set z of index.th arc's i'th data point
        void z(double newValue, int index, int i)
        {
            if (index != -1)
            {
                AlgebraicHyperbolicArc3* myarc = _attributes[index]->arc;
                myarc->operator [](i).z() = newValue;
                testNeighbours(index, i);
            }
        }


        void set_alpha(double value)
        {
            _alpha = value;
            for (GLuint i = 0; i < _attributes.size(); i++)
            {
                double u_min, u_max;
                AlgebraicHyperbolicArc3* myarc = _attributes[i]->arc;
                myarc->set_alpha(value);
                myarc->GetDefinitionDomain(u_min, u_max);
                myarc->SetDefinitionDomain(u_min, _alpha);
            }
        }




        // set the redness of index.th arc
        void set_red(double newValue, int index)
        {
            if (index != -1)
            {
                Color4* mycolor = _attributes[index]->color;
                mycolor->r() = newValue;
            }
        }

        // set the greenness of index.th arc'
        void set_green(double newValue, int index)
        {
            if (index != -1)
            {
                Color4* mycolor = _attributes[index]->color;
                mycolor->g() = newValue;
            }
        }

        // set the blueness of index.th arc
        void set_blue(double newValue, int index)
        {
            if (index != -1)
            {
                Color4* mycolor = _attributes[index]->color;
                mycolor->b() = newValue;
            }
        }





        // insert new isolated arc
        void insertArc(AlgebraicHyperbolicArc3* newArc, Color4* c)
        {
            std::shared_ptr<ArcAttributes> a = std::make_shared<ArcAttributes>();
            a->arc = new AlgebraicHyperbolicArc3(_alpha);

            if (_attributes.size() == 0)
                this->set_alpha(newArc->get_alpha());

            for (int i = 0; i < 4; i++)
            {
                a->arc->operator [](i) = newArc->operator [](i);
            }

            a->arc->UpdateVertexBufferObjectsOfData();

            a->image = a->arc->GenerateImage(30, 30, GL_STATIC_DRAW);
            a->image->UpdateVertexBufferObjects();

            a->color = new Color4();
            a->color->r() = c->r();
            a->color->g() = c->g();
            a->color->b() = c->b();

            a->next = nullptr;
            a->previous = nullptr;

            _attributes.push_back(a);
        }

        //hackerman
        void insertArc(AlgebraicHyperbolicArc3* newArc)
        {
            std::shared_ptr<ArcAttributes> a = std::make_shared<ArcAttributes>();
            a->arc = new AlgebraicHyperbolicArc3(_alpha);

            if (_attributes.size() == 0)
                this->set_alpha(newArc->get_alpha());

            for (int i = 0; i < 4; i++)
            {
                a->arc->operator [](i) = newArc->operator [](i);
            }

            a->arc->UpdateVertexBufferObjectsOfData();

            a->image = a->arc->GenerateImage(30, 30, GL_STATIC_DRAW);
            a->image->UpdateVertexBufferObjects();

            a->color = new Color4();
            a->color->r() = 1.0;
            a->color->g() = 0.0;
            a->color->b() = 0.0;

            a->next = nullptr;
            a->previous = nullptr;

            _attributes.push_back(a);
        }

        // delete arc
        void deleteArc(int index)
        {
            if (_attributes.size() != 0)
            {
                std::shared_ptr<ArcAttributes> address = _attributes[index];

                for (size_t i = 0; i < _attributes.size(); i++)
                {
                    if (_attributes[i]->next == address)
                        _attributes[i]->next = nullptr;

                    if (_attributes[i]->previous == address)
                        _attributes[i]->previous = nullptr;
                }
              
                if (_attributes[index]->arc != nullptr)
                    delete _attributes[index]->arc;
                if (_attributes[index]->image != nullptr)
                    delete _attributes[index]->image;
                if (_attributes[index]->color != nullptr)
                    delete _attributes[index]->color;

                _attributes.erase(_attributes.begin()+index);

            }
        }

        // continue existing arc (jobbrol vagy balrol) - jobb
        void continueArc(int index, bool direction)
        {
            if (index != -1)
            {
                std::shared_ptr<ArcAttributes> arcToBeContinued = _attributes[index];

                DCoordinate3 firstPoint;
                DCoordinate3 secondPoint;

                if (direction)              // jobbra
                {
                    firstPoint = arcToBeContinued->arc->operator [](3);
                    secondPoint = arcToBeContinued->arc->operator [](2);
                }
                else                        // balra
                {
                    firstPoint = arcToBeContinued->arc->operator [](0);
                    secondPoint = arcToBeContinued->arc->operator [](1);
                }

                std::shared_ptr<ArcAttributes> a = std::make_shared<ArcAttributes>();
                a->arc = new AlgebraicHyperbolicArc3(_alpha);

                // a meghosszabbitas egy ugy gorbe
                a->arc->operator [](0) = firstPoint;
                a->arc->operator [](1) = firstPoint + (firstPoint - secondPoint);
                a->arc->operator [](2) = firstPoint + 2*(firstPoint - secondPoint);
                a->arc->operator [](3) = firstPoint + 3*(firstPoint - secondPoint);

                a->arc->UpdateVertexBufferObjectsOfData();

                a->image = a->arc->GenerateImage(30, 30, GL_STATIC_DRAW);
                a->image->UpdateVertexBufferObjects();

                a->color = new Color4();
                a->color->r() = arcToBeContinued->color->r();
                a->color->g() = arcToBeContinued->color->g();
                a->color->b() = arcToBeContinued->color->b();

                a->next = nullptr;
                a->previous = nullptr;


                _attributes.push_back(a);

                // beallitjuk szomszednak
                if (direction)              // jobbra hosszabbitottunk -> az elsonek a jobb szomszedja
                {
                    _attributes[index]->next = a;
                    a->previous = _attributes[index];
                }
                else                        // balra hosszabbitottunk -> az elsonek a bal szomszedja
                {
                    _attributes[index]->previous = a;
                    a->previous = _attributes[index];
                }
            }
        }




        // test neighbours if a control point was modified
        void testNeighbours(int index, int i)
        {
            if (index != -1)
            {
                std::shared_ptr<ArcAttributes> modified = _attributes[index];
                std::shared_ptr<ArcAttributes> neighbour;
                if (i == 0 || i == 1)           // a bal szomszedot kell modositani
                {
                    neighbour = modified->previous;
                    if (neighbour)
                    {
                        if (i == 0)                 // ha az osszekapcsolt pont valtozott meg
                        {
                            if (neighbour->next == _attributes[index])           // ha a szomszed arcnak a jobb szomszedja a megvaltozott arc
                            {
                                (neighbour->arc->operator [](3)).x() = modified->arc->operator [](0).x();
                                (neighbour->arc->operator [](3)).y() = modified->arc->operator [](0).y();
                                (neighbour->arc->operator [](3)).z() = modified->arc->operator [](0).z();

                                (neighbour->arc->operator [](2)).x() = 2 * modified->arc->operator [](0).x() - modified->arc->operator [](1).x();
                                (neighbour->arc->operator [](2)).y() = 2 * modified->arc->operator [](0).y() - modified->arc->operator [](1).y();
                                (neighbour->arc->operator [](2)).z() = 2 * modified->arc->operator [](0).z() - modified->arc->operator [](1).z();
                            }
                            else if (neighbour->previous == _attributes[index])
                            {
                                (neighbour->arc->operator [](0)).x() = modified->arc->operator [](0).x();
                                (neighbour->arc->operator [](0)).y() = modified->arc->operator [](0).y();
                                (neighbour->arc->operator [](0)).z() = modified->arc->operator [](0).z();

                                (neighbour->arc->operator [](1)).x() = 2 * modified->arc->operator [](0).x() - modified->arc->operator [](1).x();
                                (neighbour->arc->operator [](1)).y() = 2 * modified->arc->operator [](0).y() - modified->arc->operator [](1).y();
                                (neighbour->arc->operator [](1)).z() = 2 * modified->arc->operator [](0).z() - modified->arc->operator [](1).z();
                            }
                        }
                        else if (i == 1)
                        {
                            if (neighbour->next == _attributes[index])           // ha a szomszed arcnak a jobb szomszedja a megvaltozott arc
                            {
                                (neighbour->arc->operator [](2)).x() = 2 * modified->arc->operator [](0).x() - modified->arc->operator [](1).x();
                                (neighbour->arc->operator [](2)).y() = 2 * modified->arc->operator [](0).y() - modified->arc->operator [](1).y();
                                (neighbour->arc->operator [](2)).z() = 2 * modified->arc->operator [](0).z() - modified->arc->operator [](1).z();
                            }
                            else if (neighbour->previous == _attributes[index])
                            {
                                (neighbour->arc->operator [](1)).x() = 2 * modified->arc->operator [](0).x() - modified->arc->operator [](1).x();
                                (neighbour->arc->operator [](1)).y() = 2 * modified->arc->operator [](0).y() - modified->arc->operator [](1).y();
                                (neighbour->arc->operator [](1)).z() = 2 * modified->arc->operator [](0).z() - modified->arc->operator [](1).z();
                            }
                        }
                    }
                }
                else                // jobb szomszedot kell modositani
                {
                    neighbour = modified->next;
                    if (neighbour)
                    {
                        if (i == 3)                 // ha az osszekapcsolt pont valtozott meg
                        {
                            if (neighbour->next == _attributes[index])           // ha a szomszed arcnak a jobb szomszedja a megvaltozott arc
                            {
                                (neighbour->arc->operator [](3)).x() = modified->arc->operator [](3).x();
                                (neighbour->arc->operator [](3)).y() = modified->arc->operator [](3).y();
                                (neighbour->arc->operator [](3)).z() = modified->arc->operator [](3).z();

                                (neighbour->arc->operator [](2)).x() = 2 * modified->arc->operator [](3).x() - modified->arc->operator [](2).x();
                                (neighbour->arc->operator [](2)).y() = 2 * modified->arc->operator [](3).y() - modified->arc->operator [](2).y();
                                (neighbour->arc->operator [](2)).z() = 2 * modified->arc->operator [](3).z() - modified->arc->operator [](2).z();
                            }
                            else if (neighbour->previous == _attributes[index])
                            {
                                (neighbour->arc->operator [](0)).x() = modified->arc->operator [](3).x();
                                (neighbour->arc->operator [](0)).y() = modified->arc->operator [](3).y();
                                (neighbour->arc->operator [](0)).z() = modified->arc->operator [](3).z();

                                (neighbour->arc->operator [](1)).x() = 2 * modified->arc->operator [](3).x() - modified->arc->operator [](2).x();
                                (neighbour->arc->operator [](1)).y() = 2 * modified->arc->operator [](3).y() - modified->arc->operator [](2).y();
                                (neighbour->arc->operator [](1)).z() = 2 * modified->arc->operator [](3).z() - modified->arc->operator [](2).z();
                            }
                        }
                        else if (i == 2)
                        {
                            if (neighbour->next == _attributes[index])           // ha a szomszed arcnak a jobb szomszedja a megvaltozott arc
                            {
                                (neighbour->arc->operator [](2)).x() = 2 * modified->arc->operator [](0).x() - modified->arc->operator [](1).x();
                                (neighbour->arc->operator [](2)).y() = 2 * modified->arc->operator [](0).y() - modified->arc->operator [](1).y();
                                (neighbour->arc->operator [](2)).z() = 2 * modified->arc->operator [](0).z() - modified->arc->operator [](1).z();
                            }
                            else if (neighbour->previous == _attributes[index])
                            {
                                (neighbour->arc->operator [](1)).x() = 2 * modified->arc->operator [](0).x() - modified->arc->operator [](1).x();
                                (neighbour->arc->operator [](1)).y() = 2 * modified->arc->operator [](0).y() - modified->arc->operator [](1).y();
                                (neighbour->arc->operator [](1)).z() = 2 * modified->arc->operator [](0).z() - modified->arc->operator [](1).z();
                            }
                        }
                    }
                }
            }
        }


        // join two arcs
        void joinArcs(int index, int index2, int direction, int direction2)
        {
            if (index != -1 && index2 != -1)
            {
                std::shared_ptr<ArcAttributes> joined = std::make_shared<ArcAttributes>();
                joined->arc = new AlgebraicHyperbolicArc3(_alpha);

                joined->arc->UpdateVertexBufferObjectsOfData();

                joined->image = joined->arc->GenerateImage(30, 30, GL_STATIC_DRAW);
                joined->image->UpdateVertexBufferObjects();

                joined->color = new Color4(1.0f, 0.0f, 0.0f, 1.0f);

                _attributes.push_back(joined);

                int newIndex = _attributes.size() - 1;



                // az elso arcot balrol join-oljuk
                if (direction)          // balra
                {
                    x(x(index, 0), newIndex, 3);
                    y(y(index, 0), newIndex, 3);
                    z(z(index, 0), newIndex, 3);

                    x(2*x(index, 0) - x(index, 1), newIndex, 2);
                    y(2*y(index, 0) - y(index, 1), newIndex, 2);
                    z(2*z(index, 0) - z(index, 1), newIndex, 2);

                }
                else                    // jobbra
                {
                    x(x(index, 3), newIndex, 3);
                    y(y(index, 3), newIndex, 3);
                    z(z(index, 3), newIndex, 3);

                    x(2*x(index, 3) - x(index, 2), newIndex, 2);
                    y(2*y(index, 3) - y(index, 2), newIndex, 2);
                    z(2*z(index, 3) - z(index, 2), newIndex, 2);
                }


                // a masodik arcot balrol join-oljuk
                if (direction2)          // balra
                {
                    x(x(index2, 0), newIndex, 0);
                    y(y(index2, 0), newIndex, 0);
                    z(z(index2, 0), newIndex, 0);

                    x(2*x(index2, 0) - x(index2, 1), newIndex, 1);
                    y(2*y(index2, 0) - y(index2, 1), newIndex, 1);
                    z(2*z(index2, 0) - z(index2, 1), newIndex, 1);

                }
                else                    // jobbra
                {
                    x(x(index2, 3), newIndex, 0);
                    y(y(index2, 3), newIndex, 0);
                    z(z(index2, 3), newIndex, 0);

                    x(2*x(index2, 3) - x(index2, 2), newIndex, 1);
                    y(2*y(index2, 3) - y(index2, 2), newIndex, 1);
                    z(2*z(index2, 3) - z(index2, 2), newIndex, 1);
                }


                // beallitjuk a szomszedsagi mutatokat
                if (direction)          // balra
                    _attributes[index]->previous = _attributes[newIndex];
                else
                    _attributes[index]->next = _attributes[newIndex];

                if (direction2)
                    _attributes[index2]->previous = _attributes[newIndex];
                else
                    _attributes[index2]->next = _attributes[newIndex];

                _attributes[newIndex]->previous = _attributes[index2];
                _attributes[newIndex]->next = _attributes[index];
            }
        }



        // merge two arcs
        void mergeArcs(int index, int index2, int direction, int direction2)
        {
            if (index != -1 && index2 != -1)
            {
                int masikIndex = direction ? 1 : 2;
                int masikIndex2 = direction2 ? 1 : 2;

                // az elso arcot balrol join-oljuk
                if (direction)          // balra
                {
                    x(0.5f * (x(index, 1) + x(index2, masikIndex2)), index, 0);
                    y(0.5f * (y(index, 1) + y(index2, masikIndex2)), index, 0);
                    z(0.5f * (z(index, 1) + z(index2, masikIndex2)), index, 0);

                }
                else                    // jobbra
                {
                    x(0.5f * (x(index, 2) + x(index2, masikIndex2)), index, 3);
                    y(0.5f * (y(index, 2) + y(index2, masikIndex2)), index, 3);
                    z(0.5f * (z(index, 2) + z(index2, masikIndex2)), index, 3);
                }


                // a masodik arcot balrol join-oljuk
                if (direction2)          // balra
                {
                    x(0.5f * (x(index2, 1) + x(index, masikIndex)), index2, 0);
                    y(0.5f * (y(index2, 1) + y(index, masikIndex)), index2, 0);
                    z(0.5f * (z(index2, 1) + z(index, masikIndex)), index2, 0);

                }
                else                    // jobbra
                {
                    x(0.5f * (x(index2, 2) + x(index, masikIndex)), index2, 3);
                    y(0.5f * (y(index2, 2) + y(index, masikIndex)), index2, 3);
                    z(0.5f * (z(index2, 2) + z(index, masikIndex)), index2, 3);
                }


                // beallitjuk a szomszedsagi mutatokat
                if (direction)          // balra
                    _attributes[index]->previous = _attributes[index2];
                else
                    _attributes[index]->next = _attributes[index2];

                if (direction2)
                    _attributes[index2]->previous = _attributes[index];
                else
                    _attributes[index2]->next = _attributes[index];
            }
        }


        int whichIndexIsIthNeighbour(int index, int which)
        {
            if (which == 0)        // bal szomszed
            {
                if (_attributes[index]->previous)       // ha letezik bal szomszed
                    // megkeressuk, hogy hanyadik index a szomszed
                    for (GLuint k = 0; k < _attributes.size(); k++)
                        if (_attributes[k] == _attributes[index]->previous)
                            return k;
            }
            else                    // jobb szomszed
            {
                if (_attributes[index]->next)       // ha letezik jobb szomszed
                    // megkeressuk, hogy hanyadik index a szomszed
                    for (GLuint k = 0; k < _attributes.size(); k++)
                        if (_attributes[k] == _attributes[index]->next)
                            return k;
            }
            return -1;
        }


        void setNeighbour(int index, int Nindex, int which)
        {
            if (which == 0)            // bal szomszedot allitunk
            {
                if (Nindex == -1)
                    _attributes[index]->previous = nullptr;
                else
                    _attributes[index]->previous = _attributes[Nindex];
            }
            else
            {
                if (Nindex == -1)
                    _attributes[index]->next = nullptr;
                else
                    _attributes[index]->next = _attributes[Nindex];
            }
        }


    };

}
