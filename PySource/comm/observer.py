import patterns.facade
##
# Encapsulates information about objects listening for \ref Notifications to be broadcast.  \ref Observer is responsible
# for these task:
# - Store the callback method reference of the listening objects
# - Provide write access to notifications for other contexts.
# - Provide the ability to notify listening objects.
#
#@see comm.observer.Notification
class Observer( ):

    notify = None
    context = None

    def __init__( self, notifyMethod, notifyContext ) :
        self.setNotifyMethod( notifyMethod )
        self.setNotifyContext( notifyContext )
    
    def setNotifyMethod( self, notifyMethod ) :
        self.notify = notifyMethod

    def setNotifyContext( self, notifyContext ) :
        self.context = notifyContext

    def getNotifyMethod( self ) :
        return self.notify
    
    def getNotifyContext( self ) :
        return self.context
    
    def notifyObserver( self, notification ) :
        self.getNotifyMethod( )( notification )

    def compareNotifyContext(self, obj):
        return obj is self.context

##
# The super class for objects that need to broadcast \ref Notifications for the application.
#
# @see comm.observer.Observer
# @see comm.observer.Notification
##
class Notifier( ) :
    facade = None
    
    def __init__( self ) :
        self.facade = patterns.facade.Facade.getInstance()
    
    def sendNotification( self, notificationName, body=None ) :
        self.facade.sendNotification( notificationName, body )

##
# The object that is used to pass messages within the application.
#
# @see comm.observer.Observer
# @see comm.observer.Notification
##
class Notification( ) :
    name = None
    body = None
    
    def __init__( self, name, body=None ) :
        self.name = name
        self.body = body

    def getName( self ) :
        return self.name

    def setBody( self, body ) :
        self.body = body

    def getBody( self ) :
        return self.body

    def str( self ) :
        msg = "Notification Name: " + self.name
        
        bd = "None"
        if self.body is not None:
            bd = str(self.body)

        msg += "\nBody:"+bd
        return msg
