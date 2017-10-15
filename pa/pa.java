/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.util.ArrayList;
import java.util.Scanner;


/**
 * Ejercicio 1
 * Integrantes
 *    Ricardo Pereira
 *    Moisés Berenguer
 **/

class Robot {
    public int x;
    public int y;
    public char direction;
    public int type_x;
    public int type_y;
    
    public Robot(Robot r1){
        this.x = r1.x;
        this.y = r1.y;
        this.direction = r1.direction;
        this.type_x = r1.type_x;
        this.type_y = r1.type_y;
    }
    
    public Robot(int x, int y, char direction){
        this.x = x;
        this.y = y;
        this.direction = direction;
        this.type_x = 0;
        this.type_y = 0;
    }
    
    public Robot(){
        this.x = 0;
        this.y = 0;
        this.direction = 'N';
        this.type_x = 0;
        this.type_y = 0;
    }
    
    public int getDir(){
        switch( this.direction ){
            case 'N':
                return 0;
            case 'S':
                return 1;
            case 'E':
                return 2;
            case 'O':
                return 3;
        }
        return 0;
    }   
    
    public int getDir(char dir){
        switch( dir ){
            case 'N':
                return 0;
            case 'S':
                return 1;
            case 'E':
                return 2;
            case 'O':
                return 3;
        }
        return 0;
    } 
    
    
    public boolean fueraBorde(int n){
        switch( this.direction ){
            case 'N':
                if( x - 1 >= 0 && x - 1 < n){
                    type_x = -1;
                    type_y = 0;
                    return false;
                }
                break;
            case 'S':
                if( x + 1 >= 0 && x + 1 < n){
                    type_x = 1;
                    type_y = 0;
                    return false;
                }
                break;
            case 'E':
                if( y + 1 >= 0 && y + 1 < n){
                    type_x = 0;
                    type_y = 1;
                    return false;
                }
                break;
            case 'O':
                if( y - 1 >= 0 && y - 1 < n){
                    type_x = 0;
                    type_y = -1;
                    return false;
                }
                break;  
        }       
        type_x = 0;
        type_y = 0;
        return true;
    }
    
    public int beforeChange(int type){
        if(type == 0){
            switch(this.direction){
                case 'N':
                    return getDir('E');
                case 'S':
                    return getDir('O');
                case 'E':
                    return getDir('S');
                case 'O':
                    return getDir('N');                
            }
        }else{
            switch(this.direction){
                case 'N':
                    return getDir('O');
                case 'S':
                    return getDir('E');
                case 'E':
                    return getDir('N');
                case 'O':
                    return getDir('S');                
            }
        
        }
        return 'N';
    }
    
    public void girar(int type){
        if(type == 0){
            switch(this.direction){
                case 'N':
                    this.direction = 'E';
                    break;
                case 'S':
                    this.direction = 'O';
                    break;
                case 'E':
                    this.direction = 'S';
                    break;
                case 'O':
                    this.direction = 'N';  
                    break;
            }
        }else{
            switch(this.direction){
                case 'N':
                    this.direction = 'O';
                    break;
                case 'S':
                    this.direction = 'E';
                    break;
                case 'E':
                    this.direction = 'N';
                    break;
                case 'O':
                    this.direction = 'S';  
                    break;
            }        
        }
    }
}

public class pa {
     //private static boolean[] visitiadoAnchura;
     public static char[][] g;
     public static boolean[][][] visitados_r1;
     public static boolean[][][] visitados_r2;
     public static int[][] movimientos;
     
     public static boolean visitado(Robot r1, Robot r2){
         if( visitados_r1[r1.x + r1.type_x][r1.y + r1.type_y][r1.getDir()] &&  visitados_r2[r2.x + r2.type_x][r2.y + r2.type_y][r2.getDir()]){
            r1.type_x = 0; r1.type_y = 0; r2.type_x = 0; r2.type_y = 0;
            return true;
         }
         return false;     
     }
     
     public static boolean puedeGirar(int type, Robot r1, Robot r2){
         if(type == 0){ //DERECHA
             if( visitados_r1[r1.x][r1.y][r1.beforeChange(type)] && visitados_r2[r2.x][r2.y][r2.beforeChange(type)]){
                 return false;
             }else{
                 r1.girar(type);
                 r2.girar(type);
             }
         }else{
             if( visitados_r1[r1.x][r1.y][r1.beforeChange(type)] && visitados_r2[r2.x][r2.y][r2.beforeChange(type)]){
                 return false;
             }else{
                 r1.girar(type);
                 r2.girar(type);
             }
         }
         return true;
     }
     
     public static void printRobot(Robot r1, Robot r2){
         System.out.println("------------------------------------------------");
         System.out.println("Robot 1: "+r1.x + "," + r1.y + " " + r1.direction);
         System.out.println("Robot 2: "+r2.x + "," + r2.y + " " + r2.direction);
     }
     
    public static int recorridoAnchura(Robot robot1, Robot robot2, int n) {        
//El nodo inicial ya está visitado        
        visitados_r1[robot1.x][robot1.y][robot1.getDir()] = true;
        visitados_r2[robot2.x][robot2.y][robot2.getDir()] = true;
//Cola de visitas de los nodos adyacentes
        ArrayList<Robot> cola1 = new ArrayList<Robot>();
        ArrayList<Robot> cola2 = new ArrayList<Robot>();
        movimientos[robot1.x][robot1.y] = 0;
        cola1.add(robot1);
        cola2.add(robot2);
//Hasta que visite todos los nodos
        while (!cola1.isEmpty() && !cola2.isEmpty()) {
            Robot r1_aux = new Robot(cola1.remove(0));
            Robot r2_aux = new Robot(cola2.remove(0));  
            
            if( g[r1_aux.x][r1_aux.y] == 'D' && g[r2_aux.x][r2_aux.y] == 'D' ){
                return movimientos[r1_aux.x][r1_aux.y];
            }
          //  int j = cola.remove(0); //Se saca el primero nodo de la cola
//Se busca en la matriz que representa el grafo los nodos adyacentes
            //printRobot(r1,r2);
            int mov = movimientos[r1_aux.x][r1_aux.y];
//Si es un nodo adyacente y no está visitado entonces 
//ADELANTE                
//Movimiento fuera de borde?   
                Robot r1 = new Robot(r1_aux);
                Robot r2 = new Robot(r2_aux);
                if ( (!r1.fueraBorde(n) && !r2.fueraBorde(n)) && (!visitado(r1,r2)) && !(r1.x+r1.type_x == r2.x+r2.type_x && r1.y+r1.type_y == r2.y+r2.type_y) ) {
                    if( !(g[r1.x+r1.type_x][r1.y+r1.type_y] == '*' || g[r2.x+r2.type_x][r2.y+r2.type_y] == '*')){
                        
                        r1.x += r1.type_x;
                        r1.y += r1.type_y;
                        r2.x += r2.type_x;
                        r2.y += r2.type_y;     
                        printRobot(r1,r2);                    
                        movimientos[r1.x][r1.y] = mov + 1 ;
                        visitados_r1[r1.x][r1.y][r1.getDir()] = true;
                        visitados_r2[r2.x][r2.y][r2.getDir()] = true;
                        if( g[r1.x][r1.y] == 'D' && g[r2.x][r2.y] == 'D' ){
                            return movimientos[r1.x][r1.y];
                        }
                        cola1.add(r1);
                        cola2.add(r2);
                    }
                }
                
                r1 = new Robot(r1_aux);
                r2 = new Robot(r2_aux);
                 
                if( puedeGirar(0, r1, r2)){ //DERECHA
                    movimientos[r1.x][r1.y] = mov + 1 ;
                    visitados_r1[r1.x][r1.y][r1.getDir()] = true;
                    visitados_r2[r2.x][r2.y][r2.getDir()] = true;
                    cola1.add(r1);
                    cola2.add(r2);  
                }else{
                    movimientos[r1.x][r1.y] = mov - 1 ;
                }
                
                r1 = new Robot(r1_aux);
                r2 = new Robot(r2_aux);
                if( puedeGirar(1, r1, r2) ){ //IZQUIERDA
                    movimientos[r1.x][r1.y] = mov + 1 ;
                    visitados_r1[r1.x][r1.y][r1.getDir()] = true;
                    visitados_r2[r2.x][r2.y][r2.getDir()] = true;
                    cola1.add(r1);
                    cola2.add(r2);
                }else{
                    movimientos[r1.x][r1.y] = mov - 1 ;
                }
            }
        
        return -1;//Devuelvo el recorrido del grafo en anchura
    }
    
    

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        
        while(n!=0){
            g = new char[n][n];
            visitados_r1 = new boolean[n][n][4];
            visitados_r2 = new boolean[n][n][4];
            movimientos = new int[n][n];
            boolean one_stored = false;
            Robot r1 = new Robot();
            Robot r2 = new Robot();
            for (int i = 0; i < n; i++) {
                String aux = scan.next();
                for (int j = 0; j < n; j++) {
                    g[i][j] = aux.charAt(j);
                    movimientos[i][j] = -1;
                    if(g[i][j] != '.' && g[i][j] != '*' && g[i][j] != 'D' ){
                        if (!one_stored){
                            r1 = new Robot(i, j, g[i][j]);
                            one_stored = true;
                        }else{
                            r2 = new Robot(i, j, g[i][j]);
                        }
                    }
                    for (int k = 0; k < 4; k++) {
                        if(g[i][j] != '*'){
                            visitados_r1[i][j][k] = false;
                            visitados_r2[i][j][k] = false;
                        }else{
                            visitados_r1[i][j][k] = true;
                            visitados_r2[i][j][k] = true;
                        }
                    }
                }
            } //Fin de la lectura
          /*  for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    System.out.print(g[i][j]+" ");
                }
                System.out.println("");
            }*/
            System.out.println(recorridoAnchura(r1, r2, n));
            n = scan.nextInt();        
        }
        
        
    }
    
}
