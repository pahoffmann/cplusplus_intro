template <class T>
   class SingletonBase
   {
      public:
         static T& GetInstance()
         {
            static T oInstance ; // Konstruktor der Unterklasse
            return oInstance ;
         }
 
      protected:
         SingletonBase(){}
 
      private:
         SingletonBase( const SingletonBase& ) ;
         SingletonBase& operator=( const SingletonBase& ) {return *this;}
   } ;
   

   //Aufruf der erbenden Klasse mit sich selbst in der vererbenden Klasse
   // Verwendung
   class MySingleton : public SingletonBase< MySingleton >
   {
      friend class SingletonBase< MySingleton >;
 
      private:
         MySingleton(){}
 
      //...
   };

   ///Instanziierung über MySingleton s = SingletonBase<MySingleton>.getInstance();
