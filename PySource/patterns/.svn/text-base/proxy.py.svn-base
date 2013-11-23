__author__ = 'Nephi Wright'

import comm.observer
import patterns.facade

##
# The super class for all of the concrete \ref Proxy instances within the application.  The proxy design pattern was
# used to separate the specifics of data access from the rest of the application.  This class is not intended to
# be instantiated directly, but as a scaffold for subclasses that provide specific features.
#
# @see core.Model
# @see comm.observer.Notifier
# @see patterns.facade.Facade
##
class Proxy( comm.observer.Notifier ) :
    NAME = 'DefaultProxy'
    facade = None
    proxyName = None
    data = None

    def __init__( self, proxyName=None, data=None ) :
        self.facade = patterns.facade.Facade.getInstance( )
        proxyName = proxyName or self.NAME
        if proxyName is None :
            raise ValueError( 'Proxy name cannot be None' )
        self.proxyName = proxyName
        if data :
            self.setData( data )

    def getProxyName( self ) :
        return self.proxyName

    def setData( self, data ) :
        self.data = data

    def getData( self ) :
        return self.data

    def onRegister( self ) :
        pass

    def onRemove( self ) :
        pass
