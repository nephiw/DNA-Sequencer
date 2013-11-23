import comm.observer
import patterns.facade

##
# The super class for all of the concrete \ref Mediator instances within the application.  The mediator design pattern
# was used to separate the specifics of gui implementation from the rest of the application.  This will allow the
# way that the data is displayed to be easily changed or updated. This class is not intended to be instantiated
# directly, but is a scaffold for subclasses that provide specific features.  Method descriptions are provided in the
# \ref Facade.
#
# @see core.View
# @see comm.observer.Notifier
# @see patterns.facade.Facade
##
class Mediator( comm.observer.Notifier ) :
    NAME = 'DefaultMediator'
    facade = None
    viewComponent = None
    mediatorName = None

    def __init__( self, mediatorName=None, viewComponent=None ) :
        self.facade = patterns.facade.Facade.getInstance( )
        mediatorName = mediatorName or self.NAME
        if mediatorName is None :
            raise ValueError( 'Mediator must have a name' )
        self.mediatorName = mediatorName
        self.viewComponent = viewComponent

    def getMediatorName( self ) :
        return self.mediatorName

    def setViewComponent( self, viewComponent ) :
        self.viewComponent = viewComponent

    def getViewComponent( self ) :
        return self.viewComponent

    def listNotificationInterests( self ) :
        return [ ]

    def handleNotification( self, notification ) :
        pass

    def onRegister( self ) :
        pass

    def onRemove(self) :
        pass