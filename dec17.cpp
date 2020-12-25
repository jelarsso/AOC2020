#include<fstream>
#include<iostream>
#include<string>


using namespace std;



class Conway{
    private:
    ifstream initial_state;
    bool *gamestate;
    int nx,ny,nz;



    public:
    Conway(string filename){
        
        initial_state.open(filename);
        string line;
        
        nx = 0;
        while(getline(initial_state,line)){
            ny = line.size();
            nx++;
        }

        initial_state.clear();
        initial_state.seekg(0);

        nz = 1;


        gamestate = new bool[nz*ny*nx];

        int ix = 0;
        while(getline(initial_state,line)){
            for (int iy = 0; iy<ny; ++iy){
                if (line[iy] == '#') this->set(1, ix,iy,0);
                else this->set(0, ix, iy, 0);
            }
            ++ix;
        }
    }

    bool& operator()(int ix,int iy,int iz){
        if (ix>=nx || iy>=ny || iz>=nz) throw range_error("INDEX OUT OF RANGE");
        return gamestate[ny*nx*iz + nx*iy + ix];
    }

    void set(bool val, int ix, int iy, int iz){
        if (ix>=nx || iy>=ny || iz>=nz) throw range_error("INDEX OUT OF RANGE");
        gamestate[ny*nx*iz + nx*iy + ix] = val;
    }

    void resize(int new_nx, int new_ny, const int new_nz, int shift_x, int shift_y, int shift_z){
        bool new_gamestate[new_nx*new_ny*new_nz];

        for (int ix = 0; ix<new_nx; ix++){
            for (int iy = 0; iy<new_ny; iy++){
                for (int iz = 0; iz<new_nz; iz++){
                    new_gamestate[new_nx*new_ny*iz + new_nx*iy + ix] = 0;
                } 
            }
        }

        for (int ix = 0; ix<nx; ix++){
            for (int iy = 0; iy<ny; iy++){
                for (int iz = 0; iz<nz; iz++){
                    if (iz>=0 && iz<nz && iy>=0 && iy<ny && ix>=0 && ix<nx){
                        new_gamestate[new_nx*new_ny*(iz+shift_z) + new_nx*(iy+shift_y) + ix + shift_x ] = (*this)(ix,iy,iz);
                    }
                }
            }
        }
        delete[] gamestate;
        nx = new_nx;
        ny = new_ny;
        nz = new_nz;
        
        gamestate = new bool[nx*ny*nz];
        for (int ix = 0; ix<nx; ix++){
            for (int iy = 0; iy<ny; iy++){
                for (int iz = 0; iz<nz; iz++){
                    gamestate[nx*ny*iz + nx*iy + ix] = new_gamestate[nx*ny*iz + nx*iy + ix];
                }
            }
        }

    };

    int count_neighbours_alive(int ix, int iy, int iz){
        int neighs = 0;
        for (int i = -1; i<=1; i++){
            for (int j = -1; j<=1; j++){
                for (int k = -1; k<=1; k++){
                    if (i==0 && j==0 && k==0) continue;
                    if (ix+i<0 || ix+i>=nx || iy+j<0 || iy+j>=ny || iz+k<0 || iz+k>=nz) continue;
                    neighs += (*this)(ix+i,iy+j,iz+k);
                }
            }
        }
        return neighs;
    }

    int actives(){
        int active = 0;
        for (int k=0;k<nz;k++){
            for (int i=0; i<nx; i++){
                for (int j = 0; j<ny; j++) if((*this)(i,j,k)) active++;
            }
        }
        return active;
    }

    void print_state(){
        cout << "nx = " << nx << " ny = " << ny << " nz = " << nz << endl;
        for (int k=0;k<nz;k++){
            for (int i=0; i<nx; i++){
                for (int j = 0; j<ny; j++) cout << (*this)(i,j,k);
                cout << endl;
            }
        cout << endl;
        }
    }


    void iterate(){
        // check if there is need to expand grid:
        bool posx,negx,posy,negy,posz,negz;
        posx = negx = posy = negy = posz = negz = false;
        for (int ix = 0; ix<nx; ix++){
            for (int iy = 0; iy<ny; iy++){
                for (int iz=0; iz<nz; iz++){
                    if (count_neighbours_alive(-1,iy,iz)==3) negx = true;
                    if (count_neighbours_alive(nx,iy,iz)==3) posx = true;
                    if (count_neighbours_alive(ix,-1,iz)==3) negy = true;
                    if (count_neighbours_alive(ix,ny,iz)==3) posy = true;
                    if (count_neighbours_alive(ix,iy,-1)==3) negz = true;
                    if (count_neighbours_alive(ix,iy,nz)==3) posz = true;
                }
            }
        }
        
        if (posx){
            this->resize(nx+1,ny,nz,0,0,0);
        }
        if (negx){
            this->resize(nx+1,ny,nz,1,0,0);
        }

        if (posy){
            this->resize(nx,ny+1,nz,0,0,0);
        }
        if (negy){
            this->resize(nx,ny+1,nz,0,1,0);
        }

        if (posz){
            this->resize(nx,ny,nz+1,0,0,0);
        }
        if (negz){
            this->resize(nx,ny,nz+1,0,0,1);
        }
        
        
        bool newstate[nx*ny*nz];
        for (int ix = 0; ix<nx; ix++){
            for (int iy = 0; iy<ny; iy++){
                for (int iz = 0; iz<nz; iz++){
                    newstate[nx*ny*iz + nx*iy + ix] = false;
                }
            }
        }
        bool alive;
        for (int i = 0; i<nx; i++){
            for (int j = 0; j<ny; j++){
                for (int k = 0; k<nz; k++){
                    if ((*this)(i,j,k) && (count_neighbours_alive(i,j,k)==2 || count_neighbours_alive(i,j,k)==3)) alive = true;
                    else if ( (!(*this)(i,j,k)) && count_neighbours_alive(i,j,k)==3) alive = true;  
                    else alive = false;
                    newstate[nx*ny*k + nx*j + i] = alive;
                }
            }
        }

        for (int i = 0; i<nx; i++){
            for (int j = 0; j<ny; j++){
                for (int k = 0; k<nz; k++) this->set(newstate[nx*ny*k + nx*j + i], i,j,k);
            }
        }

    };

    ~Conway(){
        delete[] gamestate;
    };


};



class Conway4d{
    private:
    ifstream initial_state;
    bool *gamestate;
    int nx,ny,nz,nw;



    public:
    Conway4d(string filename){
        
        initial_state.open(filename);
        string line;
        
        nx = 0;
        while(getline(initial_state,line)){
            ny = line.size();
            nx++;
        }

        initial_state.clear();
        initial_state.seekg(0);

        nz = 1;
        nw = 1;


        gamestate = new bool[nz*ny*nx*nw];

        int ix = 0;
        while(getline(initial_state,line)){
            for (int iy = 0; iy<ny; ++iy){
                if (line[iy] == '#') this->set(1, ix, iy, 0, 0);
                else this->set(0, ix, iy, 0, 0);
            }
            ++ix;
        }
    }

    bool& operator()(int ix,int iy,int iz, int iw){
        if (ix>=nx || iy>=ny || iz>=nz || iw>=nw) throw range_error("INDEX OUT OF RANGE");
        return gamestate[nx*ny*nz*iw + ny*nx*iz + nx*iy + ix];
    }

    void set(bool val, int ix, int iy, int iz, int iw){
        if (ix>=nx || iy>=ny || iz>=nz || iw>=nw) throw range_error("INDEX OUT OF RANGE");
        gamestate[nx*ny*nz*iw + ny*nx*iz + nx*iy + ix] = val;
    }

    void resize(int new_nx, int new_ny, int new_nz, int new_nw, int shift_x, int shift_y, int shift_z, int shift_w){
        bool new_gamestate[new_nx*new_ny*new_nz*new_nw];

        for (int ix = 0; ix<new_nx; ix++){
            for (int iy = 0; iy<new_ny; iy++){
                for (int iz = 0; iz<new_nz; iz++){
                    for (int iw=0;iw<new_nw; iw++){
                        new_gamestate[new_nx*new_ny*new_nz*iw + new_nx*new_ny*iz + new_nx*iy + ix] = 0;
                    }
                } 
            }
        }

        for (int ix = 0; ix<nx; ix++){
            for (int iy = 0; iy<ny; iy++){
                for (int iz = 0; iz<nz; iz++){
                    for (int iw = 0; iw<nw; iw++){
                        
                        new_gamestate[new_nx*new_ny*new_nz*(iw+shift_w) + new_nx*new_ny*(iz+shift_z) + new_nx*(iy+shift_y) + ix + shift_x ] = (*this)(ix,iy,iz,iw);
                    
                    }
                }
            }
        }
        delete[] gamestate;
        nx = new_nx;
        ny = new_ny;
        nz = new_nz;
        nw = new_nw;
        
        gamestate = new bool[nw*nx*ny*nz];
        for (int ix = 0; ix<nx; ix++){
            for (int iy = 0; iy<ny; iy++){
                for (int iz = 0; iz<nz; iz++){
                    for (int iw=0; iw<nw; iw++){
                        gamestate[nx*ny*nz*iw + nx*ny*iz + nx*iy + ix] = new_gamestate[nx*ny*nz*iw + nx*ny*iz + nx*iy + ix];
                    }
                }
            }
        }

    };

    int count_neighbours_alive(int ix, int iy, int iz, int iw){
        int neighs = 0;
        for (int i = -1; i<=1; i++){
            for (int j = -1; j<=1; j++){
                for (int k = -1; k<=1; k++){
                    for (int l = -1; l<=1; l++){
                        if (i==0 && j==0 && k==0 && l==0) continue;
                        if (ix+i<0 || ix+i>=nx || iy+j<0 || iy+j>=ny || iz+k<0 || iz+k>=nz || iw+l<0 || iw+l>=nw) continue;
                        if ((*this)(ix+i,iy+j,iz+k,iw+l)) neighs++;
                    }
                }
            }
        }
        return neighs;
    }

    int actives(){
        int active = 0;
        for (int k=0;k<nz;k++){
            for (int i=0; i<nx; i++){
                for (int j = 0; j<ny; j++) {
                    for (int l = 0; l<nw;l++) if((*this)(i,j,k,l)) active++;
                }
            }
        }
        return active;
    }

    void print_state(){
        cout << "nx = " << nx << " ny = " << ny << " nz = " << nz << " nw = " << nw << endl;
        for (int l=0;l<nw;l++){
            cout << "w = " << l << endl;
            for (int k=0;k<nz;k++){
                cout << "z = " << k << endl;
                for (int i=0; i<nx; i++){
                    for (int j = 0; j<ny; j++) cout << (*this)(i,j,k,l);
                    cout << endl;
                }
            cout << endl;
            }
        }
    }


    void iterate(){
        // check if there is need to expand grid:
        bool posx,negx,posy,negy,posz,negz,posw,negw;
        posx = negx = posy = negy = posz = negz = posw = negw = false;
        for (int ix = -1; ix<=nx; ix++){
            for (int iy = -1; iy<=ny; iy++){
                for (int iz=-1; iz<=nz; iz++){
                    for (int iw=-1; iw<=nw;iw++){
                        if (count_neighbours_alive(-1,iy,iz,iw)==3) negx = true;
                        if (count_neighbours_alive(nx,iy,iz,iw)==3) posx = true;
                        if (count_neighbours_alive(ix,-1,iz,iw)==3) negy = true;
                        if (count_neighbours_alive(ix,ny,iz,iw)==3) posy = true;
                        if (count_neighbours_alive(ix,iy,-1,iw)==3) negz = true;
                        if (count_neighbours_alive(ix,iy,nz,iw)==3) posz = true;
                        if (count_neighbours_alive(ix,iy,iz,-1)==3) negw = true;
                        if (count_neighbours_alive(ix,iy,iz,nw)==3) posw = true;
                    }
                }
            }
        }

        cout << posx << negx << posy << negy << posz << negz << posw << negw << endl;


        if (posx){
            this->resize(nx+1,ny,nz,nw,0,0,0,0);
        }
        if (negx){
            this->resize(nx+1,ny,nz,nw,1,0,0,0);
        }

        if (posy){
            this->resize(nx,ny+1,nz,nw,0,0,0,0);
        }
        if (negy){
            this->resize(nx,ny+1,nz,nw,0,1,0,0);
        }

        if (posz){
            this->resize(nx,ny,nz+1,nw,0,0,0,0);
        }
        if (negz){
            this->resize(nx,ny,nz+1,nw,0,0,1,0);
        }

        if (posw){
            this->resize(nx,ny,nz,nw+1,0,0,0,0);
        }
        if (negw){
            this->resize(nx,ny,nz,nw+1,0,0,0,1);
        }
        

        bool newstate[nx*ny*nz*nw];
        for (int ix = 0; ix<nx; ix++){
            for (int iy = 0; iy<ny; iy++){
                for (int iz = 0; iz<nz; iz++){
                    for (int iw = 0;iw<nw; iw++) newstate[nx*ny*nz*iw + nx*ny*iz + nx*iy + ix] = false;
                }
            }
        }
        bool alive;
        for (int i = 0; i<nx; i++){
            for (int j = 0; j<ny; j++){
                for (int k = 0; k<nz; k++){
                    for (int l = 0; l<nw; l++){
                        if ((*this)(i,j,k,l) && (count_neighbours_alive(i,j,k,l)==2 || count_neighbours_alive(i,j,k,l)==3)) alive = true;
                        else if ( (!(*this)(i,j,k,l)) && count_neighbours_alive(i,j,k,l)==3) alive = true;  
                        else alive = false;
                        newstate[nx*ny*nz*l + nx*ny*k + nx*j + i] = alive;
                    }
                }
            }
        }

        for (int i = 0; i<nx; i++){
            for (int j = 0; j<ny; j++){
                for (int k = 0; k<nz; k++) {
                    for (int l=0;l<nw;l++) this->set(newstate[nx*ny*nz*l + nx*ny*k + nx*j + i], i,j,k,l);
                }
            }
        }

    };

    ~Conway4d(){
        delete[] gamestate;
    };


};



int main(){

    Conway4d c("in17.data");
    for(int i=0;i<6;i++) c.iterate();
    cout << c.actives() << endl;

    return 0;
}