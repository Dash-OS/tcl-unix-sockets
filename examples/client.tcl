#!/usr/bin/env tclsh8.5

package require unix_sockets

proc readable {con} {
    set msg [gets $con]
    puts "got response: ($msg)"
    set ::done 1
}

set con     [unix_sockets::connect /tmp/example.socket]
puts $con "hello, world"
flush $con
chan event $con readable [list readable $con]
vwait ::done
