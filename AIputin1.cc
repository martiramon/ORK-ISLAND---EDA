#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME putin


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
  typedef vector<int> VI;
  typedef vector<VI>  VVI;
  typedef vector<bool> VB;
  typedef vector<VB> VVB;

  // Stores the location of orks.
  VVI ork_at;

  // Moves ork with identifier id.
  void bfsmove(Unit u) {        
    VVB vist(rows(),VB(cols(),false));
    queue< pair < pair <int, int>, Cell> > Q;   
    Cell c = cell(u.pos.i,u.pos.j);
    Q.push(make_pair(make_pair(u.pos.i,u.pos.j),c));    
    vist[u.pos.i][u.pos.j] = true;
    while (!Q.empty()) {
        pair <int,int> actual = Q.front().first;
        int x = actual.first;
        int y = actual.second;              
        if (y > 0 and vist[x][y-1] == false) { //ESQUERRA          
          Cell c1= cell(x,y-1);
          if (c1.type != WATER) {
            if (c1.city_id != -1 and city_owner(c1.city_id) != me()) {              
              int d=LEFT;
              Dir dir = Dir(d);
              Pos npos = u.pos + dir;
              Cell w = cell(npos);              
              if (pos_ok(npos) and w.type != WATER) {
                execute(Command(u.id,dir));                
                return;
              }
            } else if (c1.path_id != -1 and path_owner(c1.path_id) != me()) {              
              int d=LEFT;
              Dir dir = Dir(d);
              Pos npos = u.pos + dir;
              Cell w = cell(npos);              
              if (pos_ok(npos) and w.type != WATER) {
                execute(Command(u.id,dir));                
                return;
              }
            }         
            if (c1.type != WATER) {
              Q.push(make_pair(make_pair(x, y-1),c1));
            }                       
          }      
          vist[x][y-1] = true;
        }
        if (y < (cols()-1) and vist[x][y+1] == false) { //DRETA
          Cell c1= cell(x,y+1);
          if (c1.type != WATER) {        
            if (c1.city_id != -1 and city_owner(c1.city_id) != me()) {              
              int d=RIGHT;
              Dir dir = Dir(d);
              Pos npos = u.pos + dir;
              Cell w = cell(npos);              
              if (pos_ok(npos) and w.type != WATER) {
                execute(Command(u.id,dir));                
                return;
              }
            } else if (c1.path_id != -1 and path_owner(c1.path_id) != me()) {              
              int d=RIGHT;
              Dir dir = Dir(d);
              Pos npos = u.pos + dir;
              Cell w = cell(npos);              
              if (pos_ok(npos) and w.type != WATER) {
                execute(Command(u.id,dir));                
                return;
              }
            }             
            if (c1.type != WATER) {
              Q.push(make_pair(make_pair(x, y+1),c1));
            }
                 
          }
          vist[x][y+1] = true;       
        }
        if (x > 0 and vist[x-1][y] == false) { //AMUNT         
          Cell c1= cell(x-1,y);
          if (c1.type != WATER) {          
            if (c1.city_id != -1 and city_owner(c1.city_id) != me()) {              
              int d=TOP;
              Dir dir = Dir(d);
              Pos npos = u.pos + dir;
              Cell w = cell(npos);              
              if (pos_ok(npos) and w.type != WATER) {
                execute(Command(u.id,dir));                
                return;
              }
            } else if (c1.path_id != -1 and path_owner(c1.path_id) != me()) {              
              int d=TOP;
              Dir dir = Dir(d);
              Pos npos = u.pos + dir;
              Cell w = cell(npos);              
              if (pos_ok(npos) and w.type != WATER) {
                execute(Command(u.id,dir));                
                return;
              }
            }                 
            if (c1.type != WATER) {
              Q.push(make_pair(make_pair(x-1, y),c1));
            }
                             
          }
          vist[x-1][y] = true;        
        }
        if (x < (rows()-1) and vist[x+1][y] == false) { //AVALL          
          Cell c1= cell(x+1,y);
          if (c1.type != WATER) {         
            if (c1.city_id != -1 and city_owner(c1.city_id) != me()) {              
              int d=BOTTOM;
              Dir dir = Dir(d);
              Pos npos = u.pos + dir;
              Cell w = cell(npos);              
              if (pos_ok(npos) and w.type != WATER) {
                execute(Command(u.id,dir));                
                return;
              }
            } else if (c1.path_id != -1 and path_owner(c1.path_id) != me()) {
              int d=BOTTOM;
              Dir dir = Dir(d);
              Pos npos = u.pos + dir;
              Cell w = cell(npos);              
              if (pos_ok(npos) and w.type != WATER) {
                execute(Command(u.id,dir));                
                return;
              }
            }               
            if (c1.type != WATER) {
              Q.push(make_pair(make_pair(x+1, y),c1));
            }
                                           
          }
          vist[x+1][y] = true;
        }        
        Q.pop();        
      }
                                                
  }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    if (round() == 0) {
      ork_at = VVI(rows(), VI(cols(), -1));     	
    } else {
        for (int i = 0; i < rows(); ++i)
          for (int j = 0; j < cols(); ++j) {
            ork_at[i][j] = cell(i, j).unit_id; 
          }        
    } 
    VI my_orks = orks(me()); // Get the id's of my orks.
    for (int k = 0; k < int(my_orks.size()); ++k){			   
      Unit u = unit(my_orks[k]); 
      bfsmove(u);                                           
    }
  } 
};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
