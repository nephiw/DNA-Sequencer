import core
import comm.observer

class Facade( ) :
    ##
    # \ref Facade is responsible for the following tasks:
    # Initializing the \ref Model, \ref View and \ref Controller Singletons.
    # Provide global access to all of the methods provided by \ref Model, \ref View and \ref Controller.
    # Provide the ability to override the built in MVC methods.
    # Provide a single communication hub for registering \ref Commands and notifying \ref Observers
    #
    # @see core.Model
    # @see core.View
    # @see comm.observer.Observer
    # @see core.Controller
    ##
    instance = None
    controller = None
    model = None
    view = None

    ##
    # \ref Facade Implement the singleton design.
    #
    # @return the single instance of \ref Facade
    ##
    @staticmethod
    def getInstance() :
        return Facade( )

    def __new__(cls, *args, **kwargs) :
        if not cls.instance or not isinstance( cls.instance, cls ) :
            cls.instance = super( Facade, cls ).__new__( cls, *args )
            cls.instance.initializeFacade( )
        return cls.instance

    ##
    # Set the initial state for the \ref Facade
    #
    # This is called automatically by the constructor, it must be overridden in the entry point to the program to
    # provide additional state initialisation.  When overridden, the subclass' method must call
    # C{Facade.initializeFacade()} to create the rest of the MVC design pattern.
    ##
    def initializeFacade(self) :
        self.initializeController( )
        self.initializeModel( )
        self.initializeView( )

    ##
    # Called by the \ref initializeFacade method to initiate the \ref Controller at startup time, can be overridden
    # in the subclass of \ref Facade to handle different \ref Controller initialization.  Use to map \ref Command and
    # \ref Notification objects ensuring that this structure is created during the startup phase of run time.
    ##
    def initializeController(self) :
        if self.controller is not None :
            return
        self.controller = core.Controller.getInstance( )

    ##
    # Called by the \ref initializeFacade method to initiate the \ref Model as startup, can be overridden in the
    # subclass of \ref Facade to handle program specific \ref Model initialization.  A better solution is to
    # initialize the model by registering \ref Proxy modules in a \ref Command
    ##
    def initializeModel(self) :
        if self.model is not None :
            return
        self.model = core.Model.getInstance( )

    ##
    # Called by the \ref initializeFacade method to initiate the \ref View as startup, can be overridden in the
    # subclass of \ref Facade to handle program specific \ref View initialization.  A better solution is to
    # initialize the view and map \ref Mediator's and \ref View modules in a  \ref Command
    ##
    def initializeView(self) :
        if self.view is not None :
            return
        self.view = core.View.getInstance( )

    ##
    # Map an \ref Command with the \ref Controller by accessible by the \ref Notification's name.
    #
    # @param notificationName: the name of the \ref Notification to associate with the \ref Command
    # @param commandClassRef: a reference to the Class of the \ref Command
    ##
    def registerCommand(self, notificationName, commandClassRef) :
        self.controller.registerCommand( notificationName, commandClassRef )

    ##
    # Remove the \ref Notification to \ref Command mapping.
    #
    # @param notificationName: the name of the \ref Notification whose mapping will be removed.
    ##
    def removeCommand( self, notificationName ) :
        self.controller.removeCommand( notificationName )

    ##
    # Returns if the \ref Controller has a mapping to a specific \ref Notification
    #
    # @param notificationName: the name of the \ref Notification to be checked for mapping.
    ##
    def hasCommand( self, notificationName ) :
        return self.controller.hasCommand( notificationName )

    ##
    # Maps a \ref Proxy to its name so that it can be access via the \ref Facade.
    #
    # @param proxy: the \ref Proxy object to be mapped.
    ##
    def registerProxy( self, proxy ) :
        self.model.registerProxy( proxy )

    ##
    # Returns the \ref Proxy object associated with the name
    #
    # @param proxyName: the \ref Proxy object be returned.
    ##
    def retrieveProxy(self, proxyName) :
        return self.model.retrieveProxy( proxyName )

    ##
    # Unmaps the \ref Proxy with it's name.
    #
    # @param proxyName: the \ref Proxy object to be unmapped.
    ##
    def removeProxy(self, proxyName) :
        proxy = None
        if self.model is not None :
            proxy = self.model.removeProxy( proxyName )
        return proxy

    ##
    # Returns if the \ref Model has a mapping to a specific \ref Proxy
    #
    # @param notificationName: the name of the \ref Proxy to be checked for mapping.
    ##
    def hasProxy(self, proxyName) :
        return self.model.hasProxy( proxyName )

    ##
    # Maps a \ref Mediator to its name so that it can be access via the \ref Facade.
    #
    # @param proxy: the \ref Mediator object to be mapped.
    ##
    def registerMediator(self, mediator) :
        if self.view is not None :
            self.view.registerMediator( mediator )

    ##
    # Returns the \ref Mediator object associated with the name
    #
    # @param proxyName: the \ref Mediator name be returned.
    ##
    def retrieveMediator(self, mediatorName) :
        return self.view.retrieveMediator( mediatorName )

    ##
    # Unmaps the \ref Mediator with it's name.
    #
    # @param proxyName: the \ref Mediator object to be unmapped.
    ##
    def removeMediator(self, mediatorName) :
        mediator = None
        if self.view is not None :
            mediator = self.view.removeMediator( mediatorName )
        return mediator

    ##
    # Returns if the \ref View has a mapping to a specific \ref Mediator.
    #
    # @param notificationName: the name of the \ref Mediator to be checked for mapping.
    ##
    def hasMediator(self, mediatorName) :
        return self.view.hasMediator( mediatorName )

    ##
    # Create a new \ref Notification and send it to all listeners.
    #
    # This creational pattern makes it so that a new \ref Notification need not be created in the code sending the
    # message.
    #
    # @param notificationName: the name of the \ref Notification to send
    # @param body: the body of the \ref Notification (optional)
    ##
    def sendNotification( self, notificationName, body=None ) :
        self.notifyObservers( comm.observer.Notification( notificationName, body ) )

    ##
    # Allows for sending of custom \ref Notification classes using the facade if it requires more than just the
    # name and the body.
    #
    # @param notification: the \ref INotification to have the \ref View notify \ref Observers of.
    ##
    def notifyObservers( self, notification ) :
        if self.view is not None :
            self.view.notifyObservers( notification )
