/* uber-line-graph.h
 *
 * Copyright (C) 2010 Christian Hergert <chris@dronelabs.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __UBER_LINE_GRAPH_H__
#define __UBER_LINE_GRAPH_H__

#include "uber-graph.h"

G_BEGIN_DECLS

#define UBER_TYPE_LINE_GRAPH            (uber_line_graph_get_type())
#define UBER_LINE_GRAPH(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), UBER_TYPE_LINE_GRAPH, UberLineGraph))
#define UBER_LINE_GRAPH_CONST(obj)      (G_TYPE_CHECK_INSTANCE_CAST ((obj), UBER_TYPE_LINE_GRAPH, UberLineGraph const))
#define UBER_LINE_GRAPH_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  UBER_TYPE_LINE_GRAPH, UberLineGraphClass))
#define UBER_IS_LINE_GRAPH(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), UBER_TYPE_LINE_GRAPH))
#define UBER_IS_LINE_GRAPH_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  UBER_TYPE_LINE_GRAPH))
#define UBER_LINE_GRAPH_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  UBER_TYPE_LINE_GRAPH, UberLineGraphClass))

typedef struct _UberLineGraph        UberLineGraph;
typedef struct _UberLineGraphClass   UberLineGraphClass;
typedef struct _UberLineGraphPrivate UberLineGraphPrivate;

struct _UberLineGraph
{
	UberGraph parent;

	/*< private >*/
	UberLineGraphPrivate *priv;
};

struct _UberLineGraphClass
{
	UberGraphClass parent_class;
};

GType      uber_line_graph_get_type (void) G_GNUC_CONST;
GtkWidget* uber_line_graph_new      (void);

G_END_DECLS

#endif /* __UBER_LINE_GRAPH_H__ */
