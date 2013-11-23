import comm.observer

##
# \ref Controller is responsible for the following tasks:
# - Maintaining the maps from \ref Notifications to Commands.
# - Observing the \ref View for each \ref Notification that it has a map for.
# - Creating a new \ref Command to handle a \ref Notification from the \ref View when the mapping exists.
# - Calling the Commands \ref execute method and forwarding the \ref Notification.
#
# All Commands must be registered with the \ref Controller in order to be called by the application.  Since
# Commands handle all of the business logic of the application, it should be instantiated and initialized
# before the \ref Model and \ref View.  The specifics for this api are described in the \ref Facade documentation.
#
# @see core.View
# @see comm.observer.Observer
# @see comm.observer.Notification
# @see patterns.command.SimpleCommand
##
class Controller( ) :
    instance = None
    view = None
    commandMap = None

    def __new__( cls, *args ) :
        if not cls.instance or not isinstance( cls.instance, cls ) :
            cls.instance = super( Controller, cls ).__new__( cls, *args )
            cls.instance.initializeController( )
        return cls.instance

    @staticmethod
    def getInstance( ) :
        return Controller( )

    def initializeController( self ) :
        self.view = View.getInstance( )
        self.commandMap = { }

    def executeCommand( self, note ) :
        commandClassRef = self.commandMap.get( note.getName( ), None )
        if commandClassRef is None :
            return

        commandInstance = commandClassRef( )
        commandInstance.execute( note )

    def registerCommand( self, notificationName, commandClassRef ) :
        if self.commandMap.get( notificationName, None ) is None :
            self.view.registerObserver( notificationName, comm.observer.Observer( self.executeCommand, self ) )

        self.commandMap[ notificationName ] = commandClassRef

    def hasCommand( self, notificationName ) :
        return self.commandMap.get( notificationName, None ) is not None

    def removeCommand( self, notificationName ) :
        if self.hasCommand( notificationName ) :
            self.view.removeObserver( notificationName, self )
            del self.commandMap[ notificationName ]


##
# \ref Model is responsible for the following tasks:
# - Providing access to the \ref Proxy instances for the rest of the application.
# - Maintain the cache of \ref Proxy instances.
# - Provide the api for creating, accessing, and destroying \ref Proxy instances to be accessible through the \ref Facade.
#
# All \ref Proxy instances must be registered with the \ref Model in order to be accessed by the application.  The
# \ref Proxy instance's handle all of data for the application whether remote or local.  Via the \ref Facade all of
# this data is accessible to the other mvc actors. The specifics for this api are described in the \ref Facade
# documentation.
#
# @see patterns.proxy.Proxy
# @see comm.observer.Observer
# @see comm.observer.Notification
##
class Model( ) :
    instance = None
    proxyMap = None

    def __new__( cls, *args, **kwargs ) :
        if not cls.instance or not isinstance( cls.instance, cls ) :
            cls.instance = super( Model, cls ).__new__( cls, *args )
            cls.instance.initializeModel( )
        return cls.instance

    @staticmethod
    def getInstance( ) :
        return Model( )

    def initializeModel( self ) :
        self.proxyMap = { }

    def registerProxy( self, proxy ) :
        self.proxyMap[ proxy.getProxyName( ) ] = proxy
        proxy.onRegister( )

    def retrieveProxy( self, proxyName ) :
        return self.proxyMap.get( proxyName, None )

    def hasProxy( self, proxyName ) :
        return self.proxyMap.get( proxyName, None ) is not None

    def removeProxy( self, proxyName ) :
        proxy = self.proxyMap.get( proxyName, None )
        if proxy :
            del self.proxyMap[ proxyName ]
            proxy.onRemove( )
        return proxy


##
# \ref View is responsible for the following tasks:
# - Providing access to the \ref Mediator instances for the rest of the application.
# - Maintain the cache of \ref Mediator instances.
# - Provide the api for creating, accessing, and destroying \ref Mediator instances to be accessible through the \ref Facade.
# - Notifying Mediators when they are registered or removed.
# - Provide access for the \ref Observer to handle \ref Notifications driven by the user.
# - Provide a method of broadcasting \ref Notifications to the rest of the application.
#
# All ref Mediator instances must be registered with the \ref View in order to be accessed by the application, and in
# order to set the view component that it will maintain. The specifics for this api are described in the \ref Facade
# documentation.
#
# @see patterns.mediator.Mediator
# @see comm.observer.Observer
# @see comm.observer.Notification
##
class View( ) :
    instance = None
    observerMap = None
    mediatorMap = None

    def __new__( cls, *args ) :
        if not cls.instance or not isinstance( cls.instance, cls ) :
            cls.instance = super( View, cls ).__new__( cls, *args )
            cls.instance.initializeView( )
        return cls.instance

    @staticmethod
    def getInstance( ) :
        return View( )

    def initializeView( self ) :
        self.observerMap = { }
        self.mediatorMap = { }

    def registerObserver( self, notificationName, observer ) :
        if not notificationName in self.observerMap :
            self.observerMap[ notificationName ] = [ ]
        self.observerMap[ notificationName ].append( observer )

    def notifyObservers( self, notification ) :
        observers = self.observerMap.get( notification.getName( ), [ ] )[ : ]
        for obsvr in observers :
            obsvr.notifyObserver( notification )

    def removeObserver( self, notificationName, notifyContext ) :
        observers = self.observerMap[ notificationName ]

        for i in range( len( observers ) - 1, -1, -1 ) :
            if observers[ i ].compareNotifyContext( notifyContext ) :
                observers.pop( i )
                break

        if not len( observers ) :
            del self.observerMap[ notificationName ]

    def registerMediator( self, mediator ) :
        # in order to register a mediator a second time, it must be removed first.
        if mediator.getMediatorName( ) in self.mediatorMap :
            return

        self.mediatorMap[ mediator.getMediatorName( ) ] = mediator
        interests = mediator.listNotificationInterests( )
        if len( interests ) > 0 :
            obsvr = comm.observer.Observer( mediator.handleNotification, mediator )

            for i in range( 0, len( interests ) ) :
                self.registerObserver( interests[ i ], obsvr )

        mediator.onRegister( )

    def retrieveMediator( self, mediatorName ) :
        return self.mediatorMap.get( mediatorName, None )


    def removeMediator( self, mediatorName ) :
        for notificationName in self.observerMap.keys( ) :
            observers = self.observerMap[ notificationName ]
            for i in range( len( observers ) - 1, -1, -1 ) :
                if observers[ i ].compareNotifyContext( self.retrieveMediator( mediatorName ) ) :
                    observers.pop( i )

            if not len( observers ) :
                del self.observerMap[ notificationName ]

        mediator = self.mediatorMap.get( mediatorName, None )

        if mediator is not None :
            del self.mediatorMap[ mediatorName ]
            mediator.onRemove( )
        return mediator

    def hasMediator( self, mediatorName ) :
        return self.mediatorMap.get( mediatorName, None ) is not None
