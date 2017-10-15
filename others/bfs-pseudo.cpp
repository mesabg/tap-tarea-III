
BFS(grafo G, nodo_fuente s) 
{ 
   // recorremos todos los vértices del grafo inicializándolos a NO_VISITADO,
   // distancia INFINITA y padre de cada nodo NULL
   for u ∈ V[G] do
   {
      estado[u] = NO_VISITADO;
      distancia[u] = INFINITO;  //-- distancia infinita si el nodo no es alcanzable 
      padre[u] = NULL;
   }
   estado[s] = VISITADO;
   distancia[s] = 0;
   padre[s] = NULL;
   CrearCola(Q); //-- nos aseguramos que la cola está vacía
   Encolar(Q, s);
   while !vacia(Q) do
   {
      // extraemos el nodo u de la cola Q y exploramos todos sus nodos adyacentes
      u = extraer(Q);
      for  v ∈ adyacencia[u]  do
      {
         if estado[v] == NO_VISITADO then
         {
              estado[v] = VISITADO;
              distancia[v] = distancia[u] + 1;
              padre[v] = u;
              Encolar(Q, v);
         }
      }
   }
}