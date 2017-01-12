template <class T>
   class SingletonBase
   {
      public:
         static T& GetInstance()
         {
            static T oInstance ;
            return oInstance ;
         }
 
      protected:
         SingletonBase(){}
 
      private:
         SingletonBase( const SingletonBase& ) ;
         SingletonBase& operator=( const SingletonBase& ) {return *this;}
   } ;
 
   // Verwendung
   class MySingleton : public SingletonBase< MySingleton >
   {
      friend class SingletonBase< MySingleton >;
 
      private:
         MySingleton(){}
 
      //...
   };
