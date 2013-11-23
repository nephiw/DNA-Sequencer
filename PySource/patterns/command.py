import comm.observer

##
# \ref SimpleCommand handles the business logic of the application in modular chunks.
#
# \ref SimpleCommand should never be created directly, but instead subclassed.  The subclass should override the
# \ref execute method where your business logic will handle the \ref Notification or access to a \ref Proxy.
#
# @see core.Controller
# @see comm.observer.Notification
##
class SimpleCommand( comm.observer.Notifier ) :
    ##
    # Respond to \ref Notifications by running business logic implemented in \ref execute
    #
    # In the Command Pattern, the business logic typically begins with some user action, which resulted in a
    # \ref Notification being broadcast.
    #
    # @param notification: the \ref Notification to handle.
    ##
    def execute( self, notification ) :
        pass
