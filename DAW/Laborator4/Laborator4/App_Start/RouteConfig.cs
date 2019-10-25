using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;

namespace Laborator4
{
    public class RouteConfig
    {
        public static void RegisterRoutes(RouteCollection routes)
        {
            routes.IgnoreRoute("{resource}.axd/{*pathInfo}");

            routes.MapRoute(
                name: "CategoryIndex",
                url: "{controller}/{action}",
                defaults: new {controller = "Category", action = "Index"}
                );

            routes.MapRoute(
                name: "CategoryShow",
                url: "{controller}/{action}/{id}",
                defaults: new { controller = "Category", action = "Show", id = UrlParameter.Optional }
                );

            routes.MapRoute(
                name: "CategoryEdit",
                url: "{controller}/{action}",
                defaults: new { controller = "Category", action = "Edit" }
                );

            routes.MapRoute(
                name: "CategoryEdit",
                url: "{controller}/{action}/{id}",
                defaults: new { controller = "Category", action = "Edit", id = UrlParameter.Optional }
                );

            routes.MapRoute(
                name: "Default",
                url: "{controller}/{action}/{id}",
                defaults: new { controller = "Home", action = "Index", id = UrlParameter.Optional }
            );
        }
    }
}
