# Tcl unix_sockets Extension

A mirror of the work [cyan](https://sourceforge.net/u/cyan/profile/) has
provided that provide access to Unix Sockets (STREAM).  


#### Unix Sockets Summary

> A Unix domain socket or IPC socket (inter-process communication socket) is a data communications endpoint for exchanging data between processes executing on the same host operating system. Like named pipes, Unix domain sockets support transmission of a reliable stream of bytes (SOCK_STREAM, compare to TCP).

[Wikipedia](https://en.wikipedia.org/wiki/Unix_domain_socket)

## Example

```tcl
if 0 {
  @ unix_sockets Server Example @
}
package require unix_sockets

proc onReceive id {
  set data [gets $id]
  # echo received back to caller
  puts $id $data
  chan close $id
}

proc onConnect id {
  chan even $id readable [list onReceive $id]
}

set serverID [unix_sockets::listen /tmp/usock onConnect]

vwait __forever__
```

```tcl
if 0 {
  @ unix_sockets Client Example @
}
package require unix_sockets

proc onReply id {
  set data [gets $id]
  puts "receive: $data"
  set ::complete true
}

set clientID [unix_sockets::connect /tmp/usock]

chan event $clientID readable [list onReply $clientID]

puts $clientID echo
chan flush $clientID

vwait complete
```

### Other Examples

 - [cluster-comm](https://github.com/Dash-OS/cluster-comm/blob/master/cluster/protocols/cluster-unix.tcl) - unix_sockets is used to provide unix socket support to cluster-comm.
