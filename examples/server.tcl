#!/usr/bin/env tclsh8.5

package require unix_sockets

proc readable {con} {
    set msg [gets $con]
	puts stderr "Got message \"$msg\" from $con, echoing"
    puts $con $msg
    close $con
}

proc accept {con} {
    chan event $con readable [list readable $con]
}

set listen   [unix_sockets::listen /tmp/example.socket accept]

vwait ::forever
