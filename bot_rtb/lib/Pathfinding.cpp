#include "Pathfinding.h"

double pScalar(double* v1, double* v2)
{
	return (v1[0]*v2[0] + v1[1]*v2[1]);
}

double M(double* v)
{
	return (sqrtf(pow(v[0],2)+pow(v[1],2)));
}

double F(double coordRobot[], double coordDest[], double v[])
{
	double x = coordDest[0];
	double y = coordDest[1];

	double x0 = coordRobot[0];
	double y0 = coordRobot[1];

	double m = v[1]/v[0];

	return m*(x-x0)-(y-y0);
}

double AngleTo(double robot_x, double robot_y, double angleR, double to_x, double to_y)
{
    double angle = fmod(angleR, 2*M_PI);
    double coseno = cos(angle);
    double seno = sin(angle);

    double coordRobot[] = {robot_x, robot_y};
    double coordDest[] = {to_x, to_y};

    double v1[2] = {coseno, seno};
    double v2[2] = {coordDest[0]-coordRobot[0], coordDest[1]-coordRobot[1]};

    
    /*cout << "Debug coordRobot X: " << coordRobot[0] << endl;
    cout << "Debug coordRobot Y: " << coordRobot[1] << endl;
    cout << "Debug coordDest X: " << coordDest[0] << endl;
    cout << "Debug coordDest Y: " << coordDest[1] << endl;

    cout << "Debug ANGULO_BOT: " << angle*180/M_PI << endl;

    cout << "Debug v1[0]: " << v1[0] << endl;
    cout << "Debug v1[1]: " << v1[1] << endl;

    cout << "Debug v2[0]: " << v2[0] << endl;
    cout << "Debug v2[1]: " << v2[1] << endl;*/
    
    
    double cos = pScalar(v1,v2)/M(v2);
    cos = round(cos*1000000)/1000000;
    
    double angle_v1v2 = acos(cos);

    double ang = fmod(angle*180/M_PI,360);
    if(ang<0) ang+=360;
    if(F(coordRobot, coordDest, v1) < 0)
    {
            if(ang > 90 && ang < 270 || ang < -90 && ang > -270)
            {
                    angle_v1v2 = -angle_v1v2;
            }

    }
    else
    {
            if(ang < 90 || ang > 270 || ang < -270 || (ang > -90 && ang < 0))
            {
                    angle_v1v2 = -angle_v1v2;
            }

    }
    
    //cout << "Debug angulo necesario: " << angle_v1v2*180/M_PI << endl;
    
    return angle_v1v2;
}

//------------------------------------------------------------------------

bool 
Compare (const TNode *n, const TNode *m)
{
    return n->GetF() > m->GetF();
}

//------------------------------------------------------------------------

Pathfinding::Pathfinding() 
{
    Init();
}

int 
Pathfinding::CalcProb(int x, int y, double dist, double angle) 
{

    probs++;

    cout<<"Debug probs = "<<probs<<endl;

    int dist_horizontal;
    int dist_vertical;
    
    int wall_posX;
    int wall_posY;

    dist_horizontal = round(cos(angle) * dist);
    dist_vertical = round(sin(angle) * dist);

    wall_posX = round(x)+dist_horizontal;
    wall_posY = round(y)+dist_vertical;

    
    if(map1[wall_posX][wall_posY]==1)
    {
        probMap[0]++;
    }
    if(map2[wall_posX][wall_posY]==1)
    {
        probMap[1]++;
    }
    if(map3[wall_posX][wall_posY]==1)
    {
        probMap[2]++;
    }
    if(map4[wall_posX][wall_posY]==1)
    {
        probMap[3]++;
    }
    return probs;
}

void 
Pathfinding::LoadMap() 
{
    int max = probMap[0];
    int map = 0;
    
    for(int i=1;i<4;i++) 
    {
        if(probMap[i]>max)
        {
            max = probMap[i];
            map = i;
        }
    }
    
    cout<<"Debug MAPA CARGADO = mapa"<<map+1<<endl;

    if(map==0) 
    {
        world = map1;
    }
    else if(map==1) 
    {
        world = map2;
    }
    else if(map==2)
    {
        world = map3;
    }
    else
    {
        world = map4;
    }

    probs=100;
}

vector<TNode*> 
Pathfinding::GetChild(TNode* n, bool cl[][TAM])
{    
    vector<TNode*> v;
    for(int i=-1; i<=1; i++) 
    {
        for(int j=-1; j<=1; j++) 
        {
            if(n->GetX()+i>=MINX && n->GetY()+j>=MINY && n->GetX()+i<MAXX && n->GetY()+j<MAXY) 
            {
                if(!cl[n->GetX()+i][n->GetY()+j] && world[n->GetX()+i][n->GetY()+j]==0) {
                    v.push_back(new TNode(n->GetX()+i,n->GetY()+j));
                }
            }
        }
    }
    return v;
}

double 
Pathfinding::AdjCost(TNode* n, TNode* m) 
{
    if(abs(n->GetX() - m->GetX())==1 &&  abs(n->GetY() - m->GetY())==1) 
    {
        return 1.4;
    }
    else 
    {
        return 1.0;
    }
}

double 
Pathfinding::CalcH(TNode* n, TNode* m) 
{
    double distX = abs(n->GetX() - m->GetX());
    double distY = abs(n->GetY() - m->GetY());    
    
    if(distX > distY)
    {
        return (1.4*distY + (distX-distY));
    }
    else
    {
        return (1.4*distX + (distY-distX));
    }
}

int 
Pathfinding::Search(TNode* n, vector<TNode*> v) 
{
    
    int found = -1;
    
    for(int i=0; i<v.size(); i++) {
        if(v[i]->GetX() == n->GetX() && v[i]->GetY() == n->GetY()) 
        {
            found = i;
        }
    }
    
    return found;
}

vector<Node*> 
Pathfinding::Astar(int startx, int starty, int goalx, int goaly) 
{
    cout<<"Debug inicio= "<<startx<<" "<<starty<<" final=  "<<goalx<<" "<<goaly<<endl;

    vector<Node*> path = vector<Node*>();
    
    startx+=10;
    starty = abs(starty-10);
    
    goalx+=10;
    goaly = abs(goaly-10);
    
    vector<TNode*> openedList;
    bool closedList[TAM][TAM];

    for(int i=0;i<TAM;i++) {
        for(int j=0;j<TAM;j++) {
            closedList[i][j] = false;
        }
    }
    
    //inicializacion de la meta, el origen y de la lista abierta
    TNode *goal = new TNode(goaly, goalx);
    TNode *start =  new TNode(starty, startx);
    openedList.push_back(start);

    while(openedList.size()!=0) 
    {
        
        //obtener nodo de listaFrontera con menor f y añadir a la lista interior
        sort(openedList.begin(),openedList.end(),Compare);   
        
        TNode* n = openedList.back();
        openedList.pop_back();

        closedList[n->GetX()][n->GetY()] = true;

        //si n es meta reconstruir camino
        if(n->GetX()==goal->GetX() && n->GetY()==goal->GetY()) 
        {
            
            path.push_back(new Node(n));
            
            while(n->GetPadre()!=NULL && !(n->GetX()==start->GetX() && n->GetY()==start->GetY()))
            {
                n = n->GetPadre();
                path.push_back(new Node(n));
                //cout<<"Debug x= "<<n->GetX()-10<<" y=  "<<10-n->GetY()<<endl;
            }

            return path;
        }

        //para cada hijo m de n que no esté en lista cerrada
        vector<TNode*> hijos = GetChild(n,closedList);
        TNode *m = new TNode();

        for(int i=0; i<hijos.size(); i++) 
        {

            m = hijos[i];
            double g = n->GetG() + AdjCost(n,m);
            double h = CalcH(m,goal);
            
            //si m no está en listaFrontera
            int pos = Search(m, openedList);
            if(pos==-1) 
            {
                //almacenar la f, g y h del nodo y padre
                m->SetG(g);
                m->SetH(h);
                m->SetF(g + h);
                m->SetPadre(n);

                openedList.push_back(m);
            }
            //sino si g'(m) es mejor que m.g recalcular f y g del nodo m y establecer referencia al padre
            else if(g < m->GetG()) 
            {
                m->SetG(g);
                m->SetF(g + h);
                m->SetPadre(n);
                
                openedList.erase(openedList.begin() + pos);
                openedList.push_back(m);
            }
        }
    }
//no hay solucion
return path; 
}

void 
Pathfinding::Init()
{
    for(int i=0;i<4;i++)
    {
        probMap[i] = 0;
    }
    probs=0;
}

void 
Pathfinding::CargarMapa(const int n[][TAM]) 
{
    world = n;
}
